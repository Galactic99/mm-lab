#include <stdio.h>
typedef struct{
    int pid,at,bt,rt,ct,tat,wt,isCompleted;
}Process;

void sort(Process processes[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].at > processes[j+1].at){
                Process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
}

void rr(Process processes[],int n, int tq){
    int curr_time=processes[0].at;
    int front=0,rear=0,visited[n],queue[100],completed=0;

    for(int i=0;i<n;i++){
        visited[i]=0;
    }
    queue[rear++]=0;
    visited[0]=1;
    while(completed < n){
        int index=queue[front++];

        if(processes[index].bt <= tq){

            processes[index].ct=curr_time + processes[index].bt;
            processes[index].tat=processes[index].ct-processes[index].at;
            processes[index].wt=processes[index].tat-processes[index].bt;
            curr_time=processes[index].ct;
            processes[index].isCompleted=1;
            completed++;
        }else{

            processes[index].bt -= tq;
            curr_time+=tq;
        }

         for(int i=0;i<n;i++){
                if(!visited[i] && processes[i].at <=curr_time){
                    visited[i]=1;
                    queue[rear++]=i;
                }
            }

            if(!processes[index].isCompleted){
                queue[rear++]=index;
            }

            if(front == rear){
                for(int i=0 ;i<n;i++){
                    if(!processes[i].isCompleted){
                        if(processes[i].at > curr_time){
                            curr_time=processes[i].at;
                            visited[i]=1;
                        }
                        queue[rear++]=i;
                        break;
                    }

                }
            }
    }
}

int main(){
    int n,tq;
    printf("Enter the time quantum: \n");
    scanf("%d",&tq);
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    Process processes[n];

    for(int i=0;i<n;i++){
        printf("\nEnter the details for Process %d\n",i+1);
        processes[i].pid=i+1;
        processes[i].isCompleted=0;
        printf("Enter the arrival time , burst time : ");
        scanf("%d %d",&processes[i].at,&processes[i].bt);
    }

    sort(processes,n);
    rr(processes,n,tq);

    printf("PID\tAT\tBT\tCT\tTAT\tWT \n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].at,processes[i].bt,processes[i].ct,processes[i].tat,processes[i].wt);
    }
}