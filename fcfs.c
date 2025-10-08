#include <stdio.h>
typedef struct{
    int pid,at,bt,ct,tat,wt;
}process;

void sort(process processes[],int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].at > processes[j+1].at){
                process temp=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=temp;
            }
        }
    }
}

void fcfs(process processes[],int n){
    int current_time=0;
    for(int i=0;i<n;i++){

        if(current_time<processes[i].at){
            current_time=processes[i].at;
        }
        current_time+=processes[i].bt;
        processes[i].ct=current_time;
        processes[i].tat=processes[i].ct-processes[i].at;
        processes[i].wt=processes[i].tat-processes[i].bt;
    }
}

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d",&n);

    process processes[n];

    for(int i=0;i<n;i++){
        printf("Enter the details for process %d\n\n",i+1);
        processes[i].pid=i+1;
        printf("Enter the arrival time and burst time: ");
        scanf("%d %d",&processes[i].at,&processes[i].bt);
    }

    sort(processes,n);
    fcfs(processes,n);

    printf("PID\tAT\tBT\tCT\tTAT\tWT \n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",processes[i].pid,processes[i].at,processes[i].bt,processes[i].ct,processes[i].tat,processes[i].wt);
    }
    
}