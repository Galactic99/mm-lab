#include <stdio.h>
typedef struct{
    int pid,at,bt,prio,ct,tat,wt,isCompleted;
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

void priority(Process processes[],int n){
    int current_time=0,completed=0;

    while(completed < n){
        int max_priority=1000,selected=-1;

        for(int i=0;i<n;i++){
            if(!processes[i].isCompleted){
                if(processes[i].prio < max_priority && processes[i].at <= current_time){
                    selected=i;
                    max_priority=processes[i].prio;
                }
            }
        }

        if(selected==-1){
            current_time++;
        }else{

            processes[selected].ct=current_time+processes[selected].bt;
            processes[selected].isCompleted=1;
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
        printf("\nEnter the details for Process %d\n",i+1);
        processes[i].pid=i+1;
        processes[i].isCompleted=0;
        printf("Enter the arrival time , burst time and priority : ");
        scanf("%d %d %d",&processes[i].at,&processes[i].bt,&processes[i].prio);
    }

    sort(processes,n);
    priority(processes,n);

    printf("PID\tAT\tBT\tCT\tTAT\tWT \n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].at,processes[i].bt,processes[i].ct,processes[i].tat,processes[i].wt);
    }
}