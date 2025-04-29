#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int pid;            // Process ID
    int arrival_time;   // Time when process arrives
    int burst_time;     // Total CPU time needed
    int remaining_time; // Time left to finish (for SRTF)
    int completion_time; // When the process finishes
    int waiting_time;    // Waiting time
    int turnaround_time; // Turnaround time
    bool completed;      // Flag for HRRN
};

int main() {
    std::vector<Process> processes;
    int n;

    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        Process p;
        std::cout << "Enter arrival time and burst time for process " << i << ": ";
        std::cin >> p.arrival_time >> p.burst_time;
        p.pid = i;
        p.remaining_time = p.burst_time;
        p.completed = false;
        processes.push_back(p);
    }

    std::cout << "\n[+] Processes loaded successfully!\n";

    int choice;
    std::cout << "Select Scheduling Algorithm:\n";
    std::cout << "1. Shortest Remaining Time First (SRTF)\n";
    std::cout << "2. Highest Response Ratio Next (HRRN)\n";
    std::cout << "Enter choice (1 or 2): ";
    std::cin >> choice;

    if (choice == 1) {
        // === SRTF Scheduling ===
        int completed = 0;
        int current_time = 0;
        int total_idle_time = 0;
        std::vector<int> gantt_chart;

        while (completed != n) {
            int idx = -1;
            int min_remaining_time = 1e9;

            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && 
                    processes[i].remaining_time > 0 &&
                    processes[i].remaining_time < min_remaining_time) {
                    min_remaining_time = processes[i].remaining_time;
                    idx = i;
                }
            }

            if (idx != -1) {
                // Process found
                processes[idx].remaining_time--;
                gantt_chart.push_back(processes[idx].pid);

                if (processes[idx].remaining_time == 0) {
                    processes[idx].completion_time = current_time + 1;
                    processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                    processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                    completed++;
                }
            } else {
                // No process ready to run (CPU Idle)
                gantt_chart.push_back(-1); // Represent idle
                total_idle_time++;
            }
            current_time++;
        }

        // Print Gantt Chart
        std::cout << "\nGantt Chart (Process IDs shown):\n";
        for (int pid : gantt_chart) {
            if (pid == -1)
                std::cout << "[Idle]";
            else
                std::cout << "[P" << pid << "]";
        }
        std::cout << "\n";

        // Calculate Averages
        double avg_wt = 0, avg_tt = 0;
        for (auto &p : processes) {
            avg_wt += p.waiting_time;
            avg_tt += p.turnaround_time;
        }
        avg_wt /= n;
        avg_tt /= n;

        double cpu_utilization = 100.0 * (current_time - total_idle_time) / current_time;
        double throughput = (double)n / current_time;

        std::cout << "\nAverage Waiting Time: " << avg_wt;
        std::cout << "\nAverage Turnaround Time: " << avg_tt;
        std::cout << "\nCPU Utilization: " << cpu_utilization << "%";
        std::cout << "\nThroughput: " << throughput << " processes/unit time\n";
    }
    else if (choice == 2) {
        // === HRRN Scheduling ===
        int completed = 0, current_time = 0;
        std::vector<int> gantt_chart;

        while (completed != n) {
            int idx = -1;
            double highest_response_ratio = -1.0;

            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                    double response_ratio = (double)(current_time - processes[i].arrival_time + processes[i].burst_time) / processes[i].burst_time;
                    if (response_ratio > highest_response_ratio) {
                        highest_response_ratio = response_ratio;
                        idx = i;
                    }
                }
            }

            if (idx != -1) {
                gantt_chart.push_back(processes[idx].pid);
                current_time += processes[idx].burst_time;
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                processes[idx].completed = true;
                completed++;
            } else {
                gantt_chart.push_back(-1); // CPU idle
                current_time++;
            }
        }

        // Print Gantt Chart
        std::cout << "\nGantt Chart (Process IDs shown):\n";
        for (int pid : gantt_chart) {
            if (pid == -1)
                std::cout << "[Idle]";
            else
                std::cout << "[P" << pid << "]";
        }
        std::cout << "\n";

        // Calculate Averages
        double avg_wt = 0, avg_tt = 0;
        for (auto &p : processes) {
            avg_wt += p.waiting_time;
            avg_tt += p.turnaround_time;
        }
        avg_wt /= n;
        avg_tt /= n;

        double cpu_utilization = 100.0 * (double)(current_time - std::count(gantt_chart.begin(), gantt_chart.end(), -1)) / current_time;
        double throughput = (double)n / current_time;

        std::cout << "\nAverage Waiting Time: " << avg_wt;
        std::cout << "\nAverage Turnaround Time: " << avg_tt;
        std::cout << "\nCPU Utilization: " << cpu_utilization << "%";
        std::cout << "\nThroughput: " << throughput << " processes/unit time\n";
    }
    else {
        std::cout << "Invalid choice.\n";
    }

    return 0;
}

