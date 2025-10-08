#include<stdio.h>
#define MAX_FRAME 3
int count[MAX_FRAME],arrival[MAX_FRAME],frames[MAX_FRAME];

int findlfu(){
    int lfu=0,min=count[0],first=arrival[0];
    for(int i=1;i<MAX_FRAME;i++){
        if( (min > count[i]) || (min == count[i] && first > arrival[i])){
            lfu=i;
            min=count[i];
            first=arrival[i];
        }
    }

    return lfu;
}

void lfu(int pages[],int n){
    int page_faults=0,curr_time=0;

    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<MAX_FRAME;j++){
            if(frames[j]==pages[i]){
                found=1;
                count[j]++;
                //arrival[j]=curr_time++;
                printf("Page Hit,page %d is in frame %d\n",pages[i],j);
                break;
            }
        }

        if(!found){
            page_faults++;
            int lfu=findlfu();
            frames[lfu]=pages[i];
            count[lfu]=1;
            arrival[lfu]=++curr_time;
            printf("Page fault,page %d is put in frame %d\n",pages[i],lfu);
        }
    }
}

int main(){
    int n;
    printf("Enter the no of pages: ");
    scanf("%d",&n);

    int pages[n];

    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }

    for(int i=0;i<MAX_FRAME;i++){
        frames[i]=-1;
        count[i]=0;
        arrival[i]=0;
    }

    lfu(pages,n);

}