#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int knapsack(vector<int>& weights, vector<int>& profits, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(
                    profits[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Display input table
    cout << "\nItems:\n";
    cout << left << setw(6) << "Item" << setw(10) << "Weight" << setw(10) << "Profit" << "\n";
    for (int i = 0; i < n; ++i) {
        cout << left << setw(6) << (i + 1) << setw(10) << weights[i] << setw(10) << profits[i] << "\n";
    }
    cout << "\nKnapsack Capacity: " << capacity << endl;

    // Backtrack to find selected items
    int w = capacity;
    vector<int> selectedItems;
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(i);  // Store 1-based index
            w -= weights[i - 1];
        }
    }

    // Output results
    cout << "\nMaximum Profit: " << dp[n][capacity] << endl;
    cout << "Items included in the knapsack: ";
    if (selectedItems.empty()) {
        cout << "None";
    } else {
        for (int i = selectedItems.size() - 1; i >= 0; --i) {
            cout << "Item " << selectedItems[i];
            if (i != 0) cout << ", ";
        }
    }
    cout << endl;

    return dp[n][capacity];
}

int main() {
    int n, capacity;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weights(n), profits(n);
    cout << "Enter weights and profits of the items:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> weights[i];
        cout << "         Profit: ";
        cin >> profits[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    knapsack(weights, profits, capacity);

    return 0;
}
