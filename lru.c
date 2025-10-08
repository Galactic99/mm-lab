#include <stdio.h>
#define FRAME_SIZE 3
int last_used[FRAME_SIZE],frames[FRAME_SIZE];

int findlru(int pages[],int n){
    int min=last_used[0],lru=0;
    for(int i=1;i<FRAME_SIZE;i++){
        if(min > last_used[i]){
            lru=i;
            min = last_used[i];
        }
    }

    return lru;
}

void lru(int pages[],int n){
    int curr_time=0,page_fault=0;

    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<FRAME_SIZE;j++){
            if(frames[j]==pages[i]){
                found=1;
                last_used[j]=curr_time++;
                printf("Page Hit,page %d is in frame %d\n",pages[i],j);
                break;
            }
        }

        if(!found){
            page_fault++;
            int lru=findlru(pages,n);
            last_used[lru]=curr_time++;
            frames[lru]=pages[i];
            printf("Page fault,page %d is put in frame %d\n",pages[i],lru);
        }
    }
}

int main(){
    int n;
    printf("Enter the number of pages: ");
    scanf("%d",&n);
    int pages[n];
    printf("Enter the page Sqeuence: ");
    for(int i=0;i<n;i++){
        scanf("%d",&pages[i]);
    }

    for(int i=0;i<FRAME_SIZE;i++){
        last_used[i]=-1;
        frames[i]=-1;
    }

    lru(pages,n);

}