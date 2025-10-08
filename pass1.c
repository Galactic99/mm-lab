#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int locctr,start;
char opcode[10],label[10],operand[10],optab_opcode[10],optab_value[10];
FILE *input,*optab,*symtab,*intermediate;
int main(){
    input=fopen("input.txt","r");
    optab=fopen("optab.txt","r");
    symtab=fopen("symtab.txt","w");
    intermediate=fopen("inter.txt","w");

    fscanf(input,"%s%s%s",label,opcode,operand);
    //printf("%s%s%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        locctr=(int)strtol(operand,NULL,16);
        printf("%X",locctr);
        start=locctr;

        fprintf(intermediate,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        fscanf(input,"%s%s%s",label,opcode,operand);
    }else{
        locctr=0;
        start=locctr;
    }

    while(strcmp(opcode,"END")!=0){
        //printf("%d",locctr);
        if(strcmp(label,"*")!=0){
            fprintf(symtab,"%-8s\t%04X\n",label,locctr);
        }
        fprintf(intermediate,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);

        int found=0;
        rewind(optab);

        while(fscanf(optab,"%s%s",optab_opcode,optab_value)==2  ){
            if(strcmp(opcode,optab_opcode)==0){
                locctr+=3;
                found=1;
                break;
            }

        }

        if(!found){
            if(strcmp(opcode,"WORD")==0){
                locctr+=3;
            }else if(strcmp(opcode,"RESW")==0){
                locctr+=3*atoi(operand);
            }else if(strcmp(opcode,"RESB")==0){
                locctr+=atoi(operand);
            }else if(strcmp(opcode,"BYTE")==0){
                if(operand[0]=='C'){
                    locctr+=strlen(operand)-3;
                }else if(operand[0]=='X'){
                    locctr+=(strlen(operand)-3)/2;
                }
            }
        }

        //fprintf(intermediate,"%04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
        int n = fscanf(input, "%s%s%s", label, opcode, operand);
        if (n != 3) break;
    }
    fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

}