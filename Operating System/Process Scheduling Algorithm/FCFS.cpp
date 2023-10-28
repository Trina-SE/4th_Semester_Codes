#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int finishingTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrivalTime(Process &p1,Process &p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

void calculateTimes(vector<Process> &processes) {
    int currentTime = 0;

    for (int i = 0; i < processes.size(); ++i) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;

        processes[i].finishingTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].finishingTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].finishingTime;
    }
}

void printTable(const vector<Process> &processes) {
    cout << "Process\tArrival Time\tBurst Time\tFinishing Time\tTurnaround Time\tWaiting Time\n";
    for (const Process &p : processes) {
        cout << p.id << "\t\t" << p.arrivalTime << "\t\t" << p.burstTime << "\t\t"
             << p.finishingTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << "\n";
    }
}

int main() {
    int numProcesses;
    cout << "Enter the number of processes: ";
    cin >> numProcesses;

    vector<Process> processes(numProcesses);

    for (int i = 0; i < numProcesses; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime;
    }
    sort(processes.begin(), processes.end(), compareArrivalTime);

    calculateTimes(processes);

    cout << "\nProcess scheduling using FCFS algorithm:\n";
    printTable(processes);
    double totalTurnaroundTime = 0;
    double totalWaitingTime = 0;

    for (const Process &p : processes) {
        totalTurnaroundTime += p.turnaroundTime;
        totalWaitingTime += p.waitingTime;
    }

    double averageTurnaroundTime = totalTurnaroundTime / numProcesses;
    double averageWaitingTime = totalWaitingTime / numProcesses;

    cout << "\nAverage Turnaround Time: " << averageTurnaroundTime << endl;
    cout << "Average Waiting Time: " << averageWaitingTime << endl;

    return 0;
}
