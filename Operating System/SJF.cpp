#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;            
    int arrival_time;   
    int burst_time;     
    int remaining_time;
};

void sort_by_arrival_time(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });
}

void sjf_non_preemptive(vector<Process> &processes) {
    sort_by_arrival_time(processes);
    
    int total_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    
    cout << "PID\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";

    for (const Process &p : processes) {
        total_time += p.burst_time;
        int turnaround_time = total_time - p.arrival_time;
        int waiting_time = turnaround_time - p.burst_time;
        
        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;
        
        cout << p.pid << "\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t"
             << total_time << "\t\t" << turnaround_time << "\t\t" << waiting_time << "\n";
    }

    float average_turnaround_time = static_cast<float>(total_turnaround_time) / processes.size();
    float average_waiting_time = static_cast<float>(total_waiting_time) / processes.size();
    
    cout << "\nAverage Turnaround Time: " << average_turnaround_time << endl;
    cout << "Average Waiting Time: " << average_waiting_time << endl;
}

void sjf_preemptive(vector<Process> &processes) {
    sort_by_arrival_time(processes);
    
    int total_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int completed = 0;
    
    cout << "PID\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n";

    while (completed < processes.size()) {
        int shortest_index = -1;
        int shortest_burst = 999999; 
        
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time <= total_time && processes[i].remaining_time > 0 &&
                processes[i].burst_time < shortest_burst) {
                shortest_index = i;
                shortest_burst = processes[i].burst_time;
            }
        }
        
        if (shortest_index == -1) {
            total_time++;
            continue;
        }
        
        processes[shortest_index].remaining_time--;
        total_time++;

        if (processes[shortest_index].remaining_time == 0) {
            completed++;
            int turnaround_time = total_time - processes[shortest_index].arrival_time;
            int waiting_time = turnaround_time - processes[shortest_index].burst_time;
            
            total_turnaround_time += turnaround_time;
            total_waiting_time += waiting_time;
            
            cout << processes[shortest_index].pid << "\t" << processes[shortest_index].arrival_time << "\t\t"
                 << processes[shortest_index].burst_time << "\t\t" << total_time << "\t\t"
                 << turnaround_time << "\t\t" << waiting_time << "\n";
        }
    }

    float average_turnaround_time = static_cast<float>(total_turnaround_time) / processes.size();
    float average_waiting_time = static_cast<float>(total_waiting_time) / processes.size();
    
    cout << "\nAverage Turnaround Time: " << average_turnaround_time << endl;
    cout << "Average Waiting Time: " << average_waiting_time << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    cout << "\nSJF Non-Preemptive Scheduling:\n";
    sjf_non_preemptive(processes);
    
    cout << "\nSJF Preemptive Scheduling:\n";
    sjf_preemptive(processes);

    return 0;
}
