// Theory:  

// The Fractional Knapsack Problem helps us pack a bag to get the maximum value while staying within a weight limit. Unlike 0/1 Knapsack, where we take whole items, here we can take fractions of items.  

// How It Works: 
// 1. Sort items by value per weight (more valuable items first).  
// 2. Pick items one by one:
//    - If the item fits, take it completely.  
//    - If not, take a fraction to fill the remaining space.  
// 3. Repeat until the bag is full.

// Efficiency: 
// Sorting takes O(n log n) time, and picking items takes O(n), making the total O(n log n). This greedy approach gives the best solution. 



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
