/*
SUBMITTED BY: SAHIL MANDI
ROLL NO: BT21ECE098
*/

#include <stdio.h>
#include <limits.h>

typedef struct Process {
    char name[5];
    int arrivalTime;
    int cpuBurstTime;
    int ioBurstTime;
    int ioAfter;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int responseTime;
    int firstResponse;
} Process;

void RoundRobin(Process *process, int n, int quantum, FILE *out) {
    int currentTime = 0;
    int completed = 0;
    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;
    float totalResponseTime = 0;

    fprintf(out,"Gantt Chart\n");
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (process[i].arrivalTime <= currentTime && process[i].remainingTime > 0) {
                if (process[i].firstResponse == -1) {
                    process[i].firstResponse = currentTime - process[i].arrivalTime;
                }

                fprintf(out,"%d %s ", currentTime, process[i].name);

                int execTime = process[i].remainingTime > quantum ? quantum : process[i].remainingTime;
                process[i].remainingTime -= execTime;
                currentTime += execTime;

                if (process[i].remainingTime == 0) {
                    completed++;
                    fprintf(out,"%d ", currentTime);
                    process[i].turnaroundTime = currentTime - process[i].arrivalTime;
                    process[i].waitingTime = currentTime - process[i].cpuBurstTime - process[i].arrivalTime;
                    process[i].responseTime = process[i].firstResponse;
                    if (process[i].waitingTime < 0) {
                        process[i].waitingTime = 0;
                    }
                    totalTurnaroundTime += process[i].turnaroundTime;
                    totalWaitingTime += process[i].waitingTime;
                    totalResponseTime += process[i].responseTime;
                } else if (process[i].remainingTime % process[i].ioAfter == 0) {
                    fprintf(out,"%d %s I/O ", currentTime, process[i].name);
                    currentTime += process[i].ioBurstTime - 1;
                }
            }
        }
        currentTime++;
    }

    fprintf(out,"\n\nPerformance Metrics\n");
    fprintf(out,"PID\tArrival Time\tCPU Burst Time\tTurnaround Time\tWaiting Time\tResponse Time\tThroughput\n");
    for (int i = 0; i < n; i++) {
        fprintf(out,"%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%.6f\n", process[i].name, process[i].arrivalTime, process[i].cpuBurstTime, process[i].turnaroundTime, process[i].waitingTime, process[i].responseTime, 1.0/process[i].turnaroundTime);
    }
    fprintf(out, "\nAverage Turnaround Time: %.2f\n", totalTurnaroundTime/n);
    fprintf(out, "Average Waiting Time: %.2f\n", totalWaitingTime/n);
    fprintf(out, "Average Response Time: %.2f\n", totalResponseTime/n);
    fprintf(out, "System Throughput: %.2f processes per unit time\n", (float)n/currentTime);
}

int main() {
    FILE *fp;
    FILE *out;
    Process process[10];
    int n = 0;
    int quantum = 5; // Change this to your desired quantum
    fp = fopen("input.txt", "r");
    out = fopen("RoundRobin5_output.txt", "w");
    if(fp == NULL || out == NULL) {
        printf("Error in opening file\n");
        return 1;
    }
    while(fscanf(fp, "%[^;];%d;%d;%d;%d\n", process[n].name, &process[n].arrivalTime, &process[n].cpuBurstTime, &process[n].ioBurstTime, &process[n].ioAfter) != EOF) {
        process[n].remainingTime = process[n].cpuBurstTime;
        process[n].firstResponse = -1;
        n++;
    }
    fclose(fp);
    RoundRobin(process, n, quantum, out);
    fclose(out);
    return 0;
}