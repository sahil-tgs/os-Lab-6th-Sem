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

void SJF(Process *process, int n, FILE *out) {
    int currentTime = 0;
    int completed = 0;
    int prev = 0;
    int min = INT_MAX;
    int shortest = 0;
    int check = 0;
    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;
    float totalResponseTime = 0;

    fprintf(out,"Gantt Chart\n");
    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if ((process[i].arrivalTime <= currentTime) && (process[i].cpuBurstTime < min) && process[i].remainingTime > 0) {
                min = process[i].cpuBurstTime;
                shortest = i;
                check = 1;
            }
        }

        if (check == 0) {
            currentTime++;
            continue;
        }

        if (process[shortest].firstResponse == -1) {
            process[shortest].firstResponse = currentTime - process[shortest].arrivalTime;
        }

        fprintf(out,"%d %s ", currentTime, process[shortest].name);

        process[shortest].remainingTime -= process[shortest].cpuBurstTime;
        currentTime += process[shortest].cpuBurstTime - 1;

        min = process[shortest].remainingTime;
        if (min == 0) {
            min = INT_MAX;
        }

        if (process[shortest].remainingTime == 0) {
            completed++;
            check = 0;
            fprintf(out,"%d ", currentTime + 1);
            process[shortest].turnaroundTime = currentTime + 1 - process[shortest].arrivalTime;
            process[shortest].waitingTime = currentTime + 1 - process[shortest].cpuBurstTime - process[shortest].arrivalTime;
            process[shortest].responseTime = process[shortest].firstResponse;
            if (process[shortest].waitingTime < 0) {
                process[shortest].waitingTime = 0;
            }
            totalTurnaroundTime += process[shortest].turnaroundTime;
            totalWaitingTime += process[shortest].waitingTime;
            totalResponseTime += process[shortest].responseTime;
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
    fp = fopen("input.txt", "r");
    out = fopen("SJF_output.txt", "w");
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
    SJF(process, n, out);
    fclose(out);
    return 0;
}