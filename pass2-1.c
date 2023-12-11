#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void main()
{
	char address[10],symbol[10],opcode[10],operand[10],optab_opcode[10],optab_nm[10],symtab_address[10],symtab_symbol[10],len[5];
	int addr,flag1,flag2,flag3,start;
	FILE *f1,*f2,*f3,*f4,*f5;
	f1=fopen("inter.txt", "r");
	f2=fopen("symtab.txt", "r");
	f3=fopen("optab.txt", "r");
	f4=fopen("object_file.txt", "w");
	f5=fopen("length.txt", "r");
	
	if (f1 == NULL || f2 == NULL || f3 == NULL || f4 == NULL || f5 == NULL) {
        printf("Error opening one or more files.\n");
        exit(1);
    }
	fscanf(f5,"%s",len);
	fscanf(f1,"%s %s %s",symbol,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		fprintf(f4,"H^%s^%s^%s\n",symbol,operand,len);
		fscanf(f1,"%s %s %s %s",address,symbol,opcode,operand);
		addr=atoi(address);
		start=addr;
	}
	fprintf(f4,"T^%d",addr);
	while(strcmp(opcode,"END")!=0)
	{
		flag1=0,flag2=0,flag3=0;
		while(!feof(f3))
		{
			fscanf(f3,"%s %s",optab_opcode,optab_nm);
			if(strcmp(opcode,optab_opcode)==0)
			{
				fprintf(f4,"^%s",optab_nm);
				rewind(f3);
				break;
			}
			else if(strcmp(opcode,"RESB")==0||strcmp(opcode,"RESW")==0)
			{
				flag3=1;
				break;
			}
			else if(strcmp(opcode,"WORD")==0||strcmp(opcode,"BYTE")==0)
			{
				flag2=1;
				break;
			}
		}
		while(!feof(f2))
		{
			fscanf(f2,"%s %s",symtab_symbol,symtab_address);
			if(strcmp(operand,symtab_symbol)==0)
			{
				fprintf(f4,"%s",symtab_address);
				rewind(f2);
				flag1=1;
				break;
			}
		}
		if(flag2==1)
		{
			fprintf(f4,"^0000%s",operand);
		}
		if(flag1==0 && flag2!=1 && flag3!=1)
		{
			fprintf(f4,"0000");
		}
		fscanf(f1,"%s %s %s %s",address,symbol,opcode,operand);
		addr=atoi(address);
	}
	fprintf(f4,"\n E^%d",start);
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);
	fclose(f5);
}
