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

struct Item {
    int weight;
    int value;
};

bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item> &items) {
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;
    int currentWeight = 0;

    for (auto item : items) {
        if (currentWeight + item.weight <= W) {
            totalValue += item.value; 
            currentWeight += item.weight;
        } else {
            double fraction = (double)(W - currentWeight) / item.weight;
            totalValue += item.value * fraction;
            break; 
        }
    }
    return totalValue;
}

int main() {
    srand(time(0)); 
    
    while (true) {
        int n;
        cout << "Enter the number of items (or 0 to exit): ";
        cin >> n;

        if (n == 0) break;

        vector<Item> items(n);
        int W;
        cout << "Enter knapsack capacity: ";
        cin >> W;

        cout << "\nGenerated Items (Weight, Value):\n";
        for (int i = 0; i < n; i++) {
            items[i].weight = rand() % 20 + 1; 
            items[i].value = rand() % 100 + 1; 
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
