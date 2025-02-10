#include <bits/stdc++.h>
using namespace std;
using namespace chrono; // For measuring execution time

struct Item {
    int value, weight;
};

// Comparator for sorting by **maximum value first**
bool cmpValue(Item a, Item b) {
    return a.value > b.value;
}

// Comparator for sorting by **minimum weight first**
bool cmpWeight(Item a, Item b) {
    return a.weight < b.weight;
}

// Comparator for sorting by **maximum value density first** (value/weight ratio)
bool cmpDensity(Item a, Item b) {
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

// Function to calculate the maximum value that can be obtained using fractional knapsack
double fractionalKnapsack(int W, vector<Item>& items, bool (*cmp)(Item, Item)) {
    // Sort items based on the given comparator function
    sort(items.begin(), items.end(), cmp);

    double maxValue = 0.0;  // Maximum value obtained
    int currentWeight = 0;  // Track the weight in the knapsack

    for (auto item : items) {
        if (currentWeight + item.weight <= W) {
            // Take the whole item
            currentWeight += item.weight;
            maxValue += item.value;
        } else {
            // Take only the fraction that fits
            int remainingWeight = W - currentWeight;
            maxValue += (item.value / (double)item.weight) * remainingWeight;
            break;
        }
    }
    return maxValue;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter max knapsack capacity: ";
    cin >> W;

    vector<Item> items(n);
    srand(time(0)); // Seed for random generation

    // Randomly generate values and weights
    cout << "\nGenerated Items (Value, Weight): ";
    for (int i = 0; i < n; i++) {
        items[i].value = rand() % 100 + 1;  // Values between 1 to 100
        items[i].weight = rand() % 50 + 1;  // Weights between 1 to 50
        cout << "(" << items[i].value << ", " << items[i].weight << ") ";
    }
    cout << endl;

    // Measure execution time for Max Value First
    auto start1 = high_resolution_clock::now();
    double maxValue1 = fractionalKnapsack(W, items, cmpValue);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    // Measure execution time for Min Weight First
    auto start2 = high_resolution_clock::now();
    double maxValue2 = fractionalKnapsack(W, items, cmpWeight);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    // Measure execution time for Max Value Density First
    auto start3 = high_resolution_clock::now();
    double maxValue3 = fractionalKnapsack(W, items, cmpDensity);
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);

    cout << "\nResults:\n";
    cout << "Max Value First: " << maxValue1 << " (Time: " << duration1.count() << " µs)\n";
    cout << "Min Weight First: " << maxValue2 << " (Time: " << duration2.count() << " µs)\n";
    cout << "Max Value Density First: " << maxValue3 << " (Time: " << duration3.count() << " µs)\n";

    return 0;
}
