#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// Structure to store items
struct Item {
    int weight;
    int value;
};

// Comparator function to sort items by value/weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2; // Sort in descending order
}

// Function to solve Fractional Knapsack
double fractionalKnapsack(int W, vector<Item> &items) {
    sort(items.begin(), items.end(), compare); // Sort items by value/weight ratio

    double totalValue = 0.0; // Total value in knapsack
    int currentWeight = 0;

    for (auto item : items) {
        if (currentWeight + item.weight <= W) {
            totalValue += item.value; // Take full item
            currentWeight += item.weight;
        } else {
            double fraction = (double)(W - currentWeight) / item.weight;
            totalValue += item.value * fraction;
            break; // Knapsack is full
        }
    }
    return totalValue;
}

int main() {
    srand(time(0)); // Seed for randomization
    
    while (true) {
        int n;
        cout << "Enter the number of items (or 0 to exit): ";
        cin >> n;

        if (n == 0) break; // Exit condition

        vector<Item> items(n);
        int W;
        cout << "Enter knapsack capacity: ";
        cin >> W;

        // Generating random weights and values
        cout << "\nGenerated Items (Weight, Value):\n";
        for (int i = 0; i < n; i++) {
            items[i].weight = rand() % 20 + 1; // Random weight between 1-20
            items[i].value = rand() % 100 + 1; // Random value between 1-100
            cout << "(" << items[i].weight << ", " << items[i].value << ") ";
        }
        cout << "\n";

        auto start = high_resolution_clock::now();
        double maxValue = fractionalKnapsack(W, items);
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Max Value: " << maxValue << "\n";
        cout << "Execution Time: " << duration.count() << " microseconds\n\n";
    }

    return 0;
}
