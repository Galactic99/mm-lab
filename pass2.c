#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *inter,*symtab,*optab,*objc;
char addr[10],opcode[10],operand[10],label[10];
char symbol[10],sym_addr[10];
char mnemonic[10],code[10];
int start,temp;


int main(){

    inter=fopen("inter.txt","r");
    optab=fopen("optab.txt","r");
    objc=fopen("object.txt","w");
    symtab=fopen("symtab.txt","r");

    int length=20;

    fscanf(inter,"%s\t%s\t%s\t%s",addr,label,opcode,operand);

    if(strcmp(opcode,"START")==0){
        start=atoi(operand);
        fprintf(objc,"H^%-6s^%06X^%06X",label,start,length);
        fscanf(inter,"%s\t%s\t%s\t%s",addr,label,opcode,operand);

    }else{
        start=0;
    }
    fprintf(objc,"T^%06X",start);


    while(strcmp(opcode,"END")!=0){
        int found=0;
        rewind(optab);
        while(fscanf(optab,"%s%s",mnemonic,code)!=EOF){
            if(strcmp(mnemonic,opcode)==0){
                found=1;
                rewind(symtab);
                int sym_found=0;

                while(fscanf(symtab,"%s%s",symbol,sym_addr)!=EOF){
                    if(strcmp(symbol,operand)==0){
                        fprintf(objc,"%s%s^",code,sym_addr);
                        sym_found=1;
                        break;

                    }

                    
                }
                if(!sym_found){
                        fprintf(objc,"%s0000^",code);
                }
                break;
            }
        }

        if(!found){

            if(strcmp(opcode,"WORD")==0){
                temp=atoi(operand);
                fprintf(objc,"%06X^",temp);


            }else if(strcmp(opcode,"BYTE")==0){
                if(operand[0]=='C'){
                    for(int i=2;i<(int)strlen(operand)-1;i++){
                        fprintf(objc,"%02X",operand[i]);
                    }
                    fprintf(objc,"^");
                }else if(operand[0]=='X'){
                    for(int i=2;i<(int)strlen(operand)-1;i++){
                        fprintf(objc,"%c",operand[i]);
                    }
                    fprintf(objc,"^");

                }
            }

        }

        fscanf(inter,"%s\t%s\t%s\t%s",addr,label,opcode,operand);

    }

    fprintf(objc,"\nE^%06X^",start);

    fclose(optab); 
    fclose(symtab); 
    //fclose(asml); 
    fclose(objc); 
    fclose(inter); 
    //fclose(leng); 
 
    printf("Pass 2 completed successfully.\n"); 
    return 0; 



}