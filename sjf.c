#include <stdio.h>
typedef struct{
    int pid,at,bt,ct,tat,wt,isCompleted;
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


void sjf(Process processes[],int n){
    int completed=0,current_time=0;

    while(completed < n){

        int selected=-1,minBt=1000;

        for(int i=0;i<n;i++){
            if(!processes[i].isCompleted){
                if(processes[i].bt<minBt && processes[i].at<=current_time){
                    selected=i;
                    minBt=processes[i].bt;
                }
                

            }
        }

        if(selected==-1){
            current_time++;
        }else{
            processes[selected].isCompleted=1;
            processes[selected].ct=current_time+processes[selected].bt;
            processes[selected].tat=processes[selected].ct-processes[selected].at;
            processes[selected].wt=processes[selected].tat-processes[selected].bt;
            current_time=processes[selected].ct;
            completed++;
        }
    }
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    Process processes[n];

    for(int i=0;i<n;i++){
        printf("Enter the details for Process %d\n\n",i+1);
        processes[i].pid=i+1;
        processes[i].isCompleted=0;
        printf("Enter the arrival time and burst time: ");
        scanf("%d %d",&processes[i].at,&processes[i].bt);
    }

    sort(processes,n);
    sjf(processes,n);

    printf("PID\tAT\tBT\tCT\tTAT\tWT \n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].at,processes[i].bt,processes[i].ct,processes[i].tat,processes[i].wt);
    }
}