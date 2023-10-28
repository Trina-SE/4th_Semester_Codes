#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int finishingTime;
    int turnaroundTime;
    int waitingTime;
};

bool compareArrivalTime(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

bool comparePriority(const Process &a, const Process &b) {
    return a.priority < b.priority;
}

void nonPreemptivePriorityScheduling(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);
    sort(processes.begin(), processes.end(), comparePriority);

    int currentTime = 0;
    for (Process &p : processes) {
        p.finishingTime = currentTime + p.burstTime;
        currentTime = p.finishingTime;
        p.turnaroundTime = p.finishingTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
    }
}

void preemptivePriorityScheduling(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), compareArrivalTime);

    int currentTime = 0;
    vector<Process> queue;

    while (!processes.empty() || !queue.empty()) {
        while (!processes.empty() && processes.front().arrivalTime <= currentTime) {
            queue.push_back(processes.front());
            processes.erase(processes.begin());
        }
        if (!queue.empty()) {
            sort(queue.begin(), queue.end(), comparePriority);
            Process &p = queue.front();
            p.burstTime--;
            currentTime++;

            if (p.burstTime == 0) {
                p.finishingTime = currentTime;
                p.turnaroundTime = p.finishingTime - p.arrivalTime;
                p.waitingTime = p.turnaroundTime - p.burstTime;
                queue.erase(queue.begin());
            }
        } else {
            currentTime++;
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time, burst time, and priority for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
    }

    vector<Process> processesCopy = processes;
    
    nonPreemptivePriorityScheduling(processes);
    cout << "Non-preemptive Priority Scheduling:" << endl;
    for (const Process &p : processes) {
        cout << "Process " << p.id << ": Finishing Time = " << p.finishingTime
             << ", Turnaround Time = " << p.turnaroundTime
             << ", Waiting Time = " << p.waitingTime << endl;
    }

    preemptivePriorityScheduling(processesCopy);
    cout << "\nPreemptive Priority Scheduling:" << endl;
    for (const Process &p : processesCopy) {
        cout << "Process " << p.id << ": Finishing Time = " << p.finishingTime
             << ", Turnaround Time = " << p.turnaroundTime
             << ", Waiting Time = " << p.waitingTime << endl;
    }

    return 0;
}
