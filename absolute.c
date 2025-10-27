#include<stdio.h>
#include<string.h>
#include<stdlib.h>



int staddr1,i,j;
char line[100],name[20],uName[20],staddr[20];

FILE *input,*output;

int main(){

    input=fopen("abs.txt","r");
    output=fopen("output.txt","w");

    fscanf(input,"%s",line);

    printf("Enter the name of the program:");
    scanf("%s",uName);

    for(i=2,j=0;i<8 && j<6;i++,j++){
        name[j]=line[i];

    }
    name[j]='\0';

    if(strcmp(name,uName)==0){

        
        do{
            fscanf(input,"%s",line);

            if(line[0]=='T'){

                for(i=2,j=0;i<8 && j<6;i++,j++){
                    staddr[j]=line[i];
                }
                staddr[j]='\0';

                staddr1=atoi(staddr);

                i=12;

                while(line[i]!='$'){
                    if(line[i]!='^'){
                        fprintf(output,"00%d\t%c%c\n",staddr1,line[i],line[i+1]);
                        staddr1++;
                        i+=2;
                    }else{
                        i++;
                    }
                }
            }

            else if(line[0]=='E'){
                fclose(input);
                exit(0);
            }
        }

        while(!feof(input));
    }
}