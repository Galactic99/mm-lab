#include<stdio.h>

void fifo(int pages[],int n,int frame[],int f_size){
    int page_fault=0,rear=-1;

    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<f_size;j++){
            if(frame[j]==pages[i]){
                found=1;
                printf("Page Hit,page %d is in frame %d\n",pages[i],j);
                break;
            }   
        }

        if(!found){
            if(rear < f_size-1){
                rear++;
            }else{
                rear=0;
            }
            page_fault+=1;
            frame[rear]=pages[i];
            printf("Page fault,page %d is put in frame %d\n",pages[i],rear);

        }

    }
    
}


int main(){
    int n,frame;
    printf("Enter the number of pages: ");
    scanf("%d",&n);
    printf("Enter the frame size: ");
    scanf("%d",&frame);
    int p[n],f[frame];
    printf("Enter the page squence: ");
    for(int i=0;i<n;i++){
        scanf("%d",&p[i]);
    }

    fifo(p,n,f,frame);
}