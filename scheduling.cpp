#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define int long long
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

const int N = 3000;

// Process Class for easy implementation
class Process {
public:
    int id, at, bt, ct, tat, wt, pr;

    Process(int id) {
        this->id = id;
        at = bt = ct = tat = wt = pr = 0;
    }

    Process() {
        id = at = bt = ct = tat = wt = pr = 0;
    }

    void calculate() {
        tat = ct - at;  // Turnaround time
        wt = tat - bt;  // Waiting time
    }
};

// Comparator for sorting processes
bool compare(const Process &a, const Process &b) {
    if (a.at < b.at) return true;
    if (a.at == b.at && a.bt < b.bt) return true;
    if (a.at == b.at && a.bt == b.bt && a.id < b.id) return true;
    return false;
}

// Round Robin Algorithm
void roundRobin(int n, vector<Process> &processes, int tq) {
    queue<Process> readyQueue;
    vector<Process> v = processes;
    sort(v.begin(), v.end(), compare);
    int currTime = 0, i = 0;

    while (i < n || !readyQueue.empty()) {
        if (readyQueue.empty()) {
            currTime = v[i].at;
            readyQueue.push(v[i]);
            i++;
        } else {
            Process p = readyQueue.front();
            readyQueue.pop();
            int timeSlice = min(tq, p.bt);
            p.bt -= timeSlice;
            currTime += timeSlice;

            while (i < n && v[i].at <= currTime) {
                readyQueue.push(v[i]);
                i++;
            }

            if (p.bt <= 0) {
                processes[p.id - 1].ct = currTime;
                processes[p.id - 1].calculate();
            } else {
                readyQueue.push(p);
            }
        }
    }
}

// First-Come-First-Serve Algorithm
void fcfs(int n, vector<Process> &processes) {
    vector<Process> v = processes;
    sort(v.begin(), v.end(), compare);
    int currTime = 0;

    for (int i = 0; i < n; i++) {
        Process &p = v[i];
        currTime = max(currTime, p.at) + p.bt;
        processes[p.id - 1].ct = currTime;
        processes[p.id - 1].calculate();
    }
}

// Shortest-Job-First Algorithm
void sjf(int n, vector<Process> &processes) {
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<Process> v = processes;
    sort(v.begin(), v.end(), compare);
    int currTime = 0, i = 0;

    while (i < n || !pq.empty()) {
        if (pq.empty()) {
            currTime = v[i].at;
            pq.push({v[i].bt, v[i].at, v[i].id});
            i++;
        } else {
            vector<int> top = pq.top();
            pq.pop();
            currTime += top[0];
            processes[top[2] - 1].ct = currTime;
            processes[top[2] - 1].calculate();

            while (i < n && v[i].at <= currTime) {
                pq.push({v[i].bt, v[i].at, v[i].id});
                i++;
            }
        }
    }
}

// Shortest-Remaining-Time-First Algorithm
void srtf(int n, vector<Process> &processes) {
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<Process> v = processes;
    sort(v.begin(), v.end(), compare);
    int currTime = 0, i = 0;

    while (i < n || !pq.empty()) {
        if (pq.empty()) {
            currTime = v[i].at;
            pq.push({v[i].bt, v[i].id});
            i++;
        } else {
            vector<int> top = pq.top();
            pq.pop();
            int nextEventTime = currTime + top[0];

            if (i < n) nextEventTime = min(v[i].at, nextEventTime);

            top[0] -= (nextEventTime - currTime);
            currTime = nextEventTime;

            if (top[0] <= 0) {
                processes[top[1] - 1].ct = currTime;
                processes[top[1] - 1].calculate();
            } else {
                pq.push({top[0], top[1]});
            }

            while (i < n && v[i].at <= currTime) {
                pq.push({v[i].bt, v[i].id});
                i++;
            }
        }
    }
}

void solve() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 1; i <= n; i++) {
        processes[i - 1] = Process(i);
        cout << "Enter the arrival time and burst time for process " << i << ": ";
        cin >> processes[i - 1].at >> processes[i - 1].bt;
    }

    // Round Robin scheduling
    int tq;
    cout << "Enter the time quantum for Round Robin: ";
    cin >> tq;
    vector<Process> rrProcesses = processes;
    roundRobin(n, rrProcesses, tq);
    cout << "Round Robin results:" << endl;
    for (int i = 0; i < n; i++)
        cout << "Process " << rrProcesses[i].id << ": CT = " << rrProcesses[i].ct << ", TAT = " << rrProcesses[i].tat << ", WT = " << rrProcesses[i].wt << endl;

    // FCFS scheduling
    vector<Process> fcfsProcesses = processes;
    fcfs(n, fcfsProcesses);
    cout << "FCFS results:" << endl;
    for (int i = 0; i < n; i++)
        cout << "Process " << fcfsProcesses[i].id << ": CT = " << fcfsProcesses[i].ct << ", TAT = " << fcfsProcesses[i].tat << ", WT = " << fcfsProcesses[i].wt << endl;

    // SJF scheduling
    vector<Process> sjfProcesses = processes;
    sjf(n, sjfProcesses);
    cout << "SJF results:" << endl;
    for (int i = 0; i < n; i++)
        cout << "Process " << sjfProcesses[i].id << ": CT = " << sjfProcesses[i].ct << ", TAT = " << sjfProcesses[i].tat << ", WT = " << sjfProcesses[i].wt << endl;

    // SRTF scheduling
    vector<Process> srtfProcesses = processes;
    srtf(n, srtfProcesses);
    cout << "SRTF results:" << endl;
    for (int i = 0; i < n; i++)
        cout << "Process " << srtfProcesses[i].id << ": CT = " << srtfProcesses[i].ct << ", TAT = " << srtfProcesses[i].tat << ", WT = " << srtfProcesses[i].wt << endl;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
