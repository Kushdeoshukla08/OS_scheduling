
 
#include <stdio.h>
#include<math.h>

 
struct Process {
    int process_id; 
    int burst_time; 
    int arrival_time; 
};
 

void findWaitingTime(Process process[], int n,
                                int waiting_time[])
{
    int rem_time[n];
 
    
    for (int i = 0; i < n; i++)
        rem_time[i] = process[i].burst_time;
 
    int completed = 0, time = 0, min = INFINITY;
    int shortest = 0, finish_time;
    bool check = false;
 
    
    while (completed != n) {
 
        
        for (int j = 0; j < n; j++) {
            if ((process[j].arrival_time <= time) &&
            (rem_time[j] < min) && rem_time[j] > 0) {
                min = rem_time[j];
                shortest = j;
                check = true;
            }
        }
 
        if (check == false) {
            time++;
            continue;
        }
 
        
        rem_time[shortest]--;
 
        
        min = rem_time[shortest];
        if (min == 0)
            min = INFINITY;
 
        
        if (rem_time[shortest] == 0) {
 
            
            completed++;
            check = false;
 
            
            finish_time = time + 1;
 
            
            waiting_time[shortest] = finish_time -
                        process[shortest].burst_time -
                        process[shortest].arrival_time;
 
            if (waiting_time[shortest] < 0)
                waiting_time[shortest] = 0;
        }
        
        time++;
    }
}
 

void findTurnAroundTime(Process process[], int n,
                        int waiting_time[], int tat[])
{
    
    for (int i = 0; i < n; i++)
        tat[i] = process[i].burst_time + waiting_time[i];
}
 

void findavgTime(Process process[], int n)
{
    int waiting_time[n], tat[n], total_wt = 0,
                    total_tat = 0;
 
    
    findWaitingTime(process, n, waiting_time);
 
    
    findTurnAroundTime(process, n, waiting_time, tat);
 
    
    printf("Process\tBurst Time\tWaiting Time\tTotal Turnaround Time");
 
    
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + waiting_time[i];
        total_tat = total_tat + tat[i];
        printf("\n%d\t\t%d\t\t%d\t\t%d\n", process[i].process_id, process[i].burst_time, waiting_time[i], tat[i]);

        
    }
 	printf("\nAverage waiting time=%f", (float)total_wt / (float)n);
printf("\nAverage turnaround time=%f", (float)total_tat / (float)n);


}
 
int main()
{
    Process process[] = { { 1, 6, 2 }, { 2, 2, 5 },
                    { 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} };
    int n = sizeof(process) / sizeof(process[0]);
 
    findavgTime(process, n);
    return 0;
}
