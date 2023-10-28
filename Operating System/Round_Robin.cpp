#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int finishing_time;
    int turnaround_time;
    int waiting_time;
};

void roundRobinScheduling(vector<Process>& processes, int quantum_time) {
    queue<int> ready_queue;
    int time = 0;
    int n = processes.size();

    while (!ready_queue.empty() || !processes.empty()) {
        while (!processes.empty() && processes.front().arrival_time <= time) {
            ready_queue.push(processes.front().id);
            processes.erase(processes.begin());
        }

        if (!ready_queue.empty()) {
            int current_process_id = ready_queue.front();
            ready_queue.pop();

            if (processes[current_process_id].remaining_time <= quantum_time) {
                time += processes[current_process_id].remaining_time;
                processes[current_process_id].finishing_time = time;
                processes[current_process_id].remaining_time = 0;
            } else {
                time += quantum_time;
                processes[current_process_id].remaining_time -= quantum_time;
                ready_queue.push(current_process_id);
            }
        } else {
            time++;
        }
    }
}

int main() {
    int n, quantum_time;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i;
        cout << "Enter arrival time and burst time for process " << i << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    cout << "Enter time quantum: ";
    cin >> quantum_time;

    roundRobinScheduling(processes, quantum_time);

    double total_turnaround_time = 0;
    double total_waiting_time = 0;

    cout << "\nProcess\tFinishing Time\tTurnaround Time\tWaiting Time\n";
    for (Process& p : processes) {
        p.turnaround_time = p.finishing_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;
        total_turnaround_time += p.turnaround_time;
        total_waiting_time += p.waiting_time;

        cout << p.id << "\t" << p.finishing_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << "\n";
    }

    double average_turnaround_time = total_turnaround_time / n;
    double average_waiting_time = total_waiting_time / n;
    cout << "\nAverage Turnaround Time: " << average_turnaround_time << "\n";
    cout << "Average Waiting Time: " << average_waiting_time << "\n";

    return 0;
}
