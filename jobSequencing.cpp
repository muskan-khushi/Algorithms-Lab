#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono; // For measuring execution time

// Structure to represent a Job
struct Job {
    int id, deadline, profit;
};

// Comparator function to sort jobs by decreasing profit
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

// Function to perform job sequencing
void jobSequencing(vector<Job> &jobs) {
    int n = jobs.size();
    
    // Sort jobs in decreasing order of profit
    sort(jobs.begin(), jobs.end(), compare);

    // Find maximum deadline
    int maxDeadline = 0;
    for (const auto &job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }

    vector<int> slots(maxDeadline + 1, -1); // Slots array
    vector<bool> slotOccupied(maxDeadline + 1, false); // To track occupied slots

    int totalProfit = 0, jobsDone = 0;

    for (int i = 0; i < n; i++) {
        for (int j = min(maxDeadline, jobs[i].deadline); j > 0; j--) {
            if (!slotOccupied[j]) { // If slot is empty
                slots[j] = jobs[i].id;
                slotOccupied[j] = true;
                totalProfit += jobs[i].profit;
                jobsDone++;
                break;
            }
        }
    }

    // Display Results
    cout << "Scheduled Jobs: ";
    for (int i = 1; i <= maxDeadline; i++) {
        if (slots[i] != -1)
            cout << slots[i] << " ";
    }
    cout << "\nTotal Profit: " << totalProfit << endl;
}

int main() {
    vector<vector<Job>> testCases = {
        {
            {1, 2, 100}, {2, 1, 50}, {3, 2, 20}, {4, 1, 70}, {5, 3, 200}
        },
        {
            {1, 4, 20}, {2, 1, 10}, {3, 1, 40}, {4, 1, 30}
        }
    };

    for (int i = 0; i < testCases.size(); i++) {
        cout << "\nTest Case " << i + 1 << ":\n";
        cout << "Input Jobs (ID, Deadline, Profit):" << endl;
        for (const auto &job : testCases[i]) {
            cout << "(" << job.id << ", " << job.deadline << ", " << job.profit << ") ";
        }
        cout << "\n";

        auto start = high_resolution_clock::now();
        jobSequencing(testCases[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout << "Execution Time: " << duration.count() << " µs\n";
    }

    return 0;
}
