#include <bits/stdc++.h>
using namespace std;

// ------------------ process Class ------------------
class process {
public:
    int id;         // process ID
    int arrival;    // Arrival Time
    int burst;      // Burst Time
    int priority;   // Priority (smaller = higher)
    int waiting;    // Waiting Time
    int turnaround; // Turnaround Time

    // Constructor
    process(int i, int a, int b, int p) {
        id = i;
        arrival = a;
        burst = b;
        priority = p;
        waiting = 0;
        turnaround = 0;
    }
};

// ------------------ FCFS Scheduling ------------------
void FCFS(vector<process> p) {
    cout << "\n===== FCFS Scheduling =====\n";

    // Sort by arrival time
    sort(p.begin(), p.end(), [](process a, process b) 
        {
            return a.arrival < b.arrival;
        }   );

    int time = 0;
    for (auto &pr : p) {
        if (time < pr.arrival)
            time = pr.arrival;          // Wait for process to arrive
        pr.waiting = time - pr.arrival; // Waiting time
        time += pr.burst;               // Move clock forward
        pr.turnaround = pr.waiting + pr.burst;
    }

    // Print results
    cout << "PID\tAT\tBT\tWT\tTAT\n";
    float totalWT = 0, totalTAT = 0;
    for (auto &pr : p) {
        cout << pr.id << "\t" << pr.arrival << "\t" << pr.burst
             << "\t" << pr.waiting << "\t" << pr.turnaround << endl;
        totalWT += pr.waiting;
        totalTAT += pr.turnaround;
    }
    cout << "Avg WT: " << totalWT / p.size()
         << "  Avg TAT: " << totalTAT / p.size() << endl;
}

// ------------------ Priority (Non-Preemptive) ------------------
void PriorityScheduling(vector<process> p) {
    cout << "\n===== Priority Scheduling (Non-Preemptive) =====\n";

    // Sort first by priority, then by arrival
    sort(p.begin(), p.end(), [](process a, process b) {
        if (a.priority == b.priority)
            return a.arrival < b.arrival;
        return a.priority < b.priority; // Lower number = higher priority
    });

    int time = 0;
    for (auto &pr : p) {
        if (time < pr.arrival)
            time = pr.arrival;
        pr.waiting = time - pr.arrival;
        time += pr.burst;
        pr.turnaround = pr.waiting + pr.burst;
    }

    // Print results
    cout << "PID\tPri\tAT\tBT\tWT\tTAT\n";
    float totalWT = 0, totalTAT = 0;
    for (auto &pr : p) {
        cout << pr.id << "\t" << pr.priority << "\t" << pr.arrival
             << "\t" << pr.burst << "\t" << pr.waiting
             << "\t" << pr.turnaround << endl;
        totalWT += pr.waiting;
        totalTAT += pr.turnaround;
    }
    cout << "Avg WT: " << totalWT / p.size()
         << "  Avg TAT: " << totalTAT / p.size() << endl;
}

// ------------------ Main Function ------------------
int main() {
    // Create process objects (using constructor)
    vector<process> processes = {
        process(1, 0, 5, 2),
        process(2, 1, 3, 1),
        process(3, 2, 8, 4),
        process(4, 3, 6, 3)
    };

    FCFS(processes);
    PriorityScheduling(processes);

    return 0;
}
