#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int start,locctr,len;
char label[10],opcode[10],operand[10],optab_opcode[10],optab_code[10];
FILE* input,*optab,*symtab,*length,*inter;

int main(){
    input=fopen("input.txt","r");
    optab=fopen("optab.txt","r");
    inter=fopen("inter.txt","w");
    symtab=fopen("symtab.txt","w");
    length=fopen("length.txt","w");

    fscanf(input,"%s%s%s",label,opcode,operand);

    if(strcmp(opcode,"START")==0){
        locctr=(int)strtol(operand,NULL,16);
        start=locctr;
        fprintf(inter,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fscanf(input,"%s%s%s",label,opcode,operand);
    }else{
        locctr=0;
        start=locctr;
    }


    while(strcmp(opcode,"END")!=0){

        if(strcmp(label,"*")!=0){
            fprintf(symtab,"%s\t%04X\n",label,locctr);
        }
        fprintf(inter,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);

        rewind(optab);
        int found=0;

        while(fscanf(optab,"%s%s",optab_opcode,optab_code)==2){
            if(strcmp(opcode,optab_opcode)==0){
                found=1;
                locctr+=3;
                break;
            }
        }

        if(!found){
            if(strcmp(opcode,"WORD")==0){
                locctr+=3;

            }else if(strcmp(opcode,"RESW")==0){
                locctr+= 3*atoi(operand);
            }else if(strcmp(opcode,"RESB")==0){
                locctr+=atoi(operand);
            }else if(strcmp(opcode,"BYTE")==0){
                if(operand[0]=='C'){
                    locctr+=strlen(operand)-3;
                }
                else if(operand[0]=='X'){
                    locctr+=(strlen(operand)-3)/2;
                }
            }
        }

        fscanf(input,"%s%s%s",label,opcode,operand);
    }

    fprintf(inter,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
    len=locctr-start;
    fprintf(length,"%X",len);
}