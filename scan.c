#include<stdio.h>
#include<math.h>

#define MAX_TRACK 199


void sort(int req[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(req[j]>req[j+1]){
                int temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }

}

void scan(int head,int n,int req[],int direc){
    int curr=head,tot_seek=0;
    int start_index=0;
    for(int i=0;i<n;i++){
        if(req[i] >= curr){
            start_index=i;
            break;
        }
    }

    if(direc){

        for(int i=start_index;i<n;i++){
            tot_seek += abs(curr - req[i]);
            curr=req[i];
            printf("%d ->",curr);

        }
        tot_seek += abs(curr - MAX_TRACK);
        curr=MAX_TRACK;

        printf("%d -> ",MAX_TRACK);


        for(int i=start_index-1;i>=0;i--){
            tot_seek += abs(curr-req[i]);
            curr=req[i];
            printf("%d -> ",curr);
        }
    }else{

        for(int i=start_index;i>=0;i--){
            tot_seek += abs(curr - req[i]);
            curr=req[i];
            printf("%d ->",curr);

        }
        tot_seek += abs(curr - 0);
        curr=0;

        printf("%d -> ",curr);


        for(int i=start_index+1;i<n;i++){
            tot_seek += abs(curr-req[i]);
            curr=req[i];
            printf("%d -> ",curr);
        }
    }

    printf("%d",tot_seek);


}

int main(){
    int head,n,direc;
    printf("Enter the number of requests: ");
    scanf("%d",&n);

    int req[n];
    printf("Enter the disk squence: ");
    for(int i=0;i<n;i++){
        scanf("%d",&req[i]);
    }

    printf("Enter the current head position: ");
    scanf("%d",&head);

    printf("Enter the direction of servicing ,right(1) left(0): ");
    scanf("%d",&direc);
    sort(req,n);
    scan(head,n,req,direc);
}