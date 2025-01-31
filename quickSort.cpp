#include <bits/stdc++.h>
using namespace std;

// Partition function for Quick Sort
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right]; // Pivot element
    int i = left - 1;       // Index of smaller element

    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

// Quick Sort function
void quickSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int part = partition(arr, left, right); // Partition index
        quickSort(arr, left, part - 1);        // Sort elements before partition
        quickSort(arr, part + 1, right);       // Sort elements after partition
    }
}

int main() {
    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000; // Generate random numbers between 0 and 999
    }

    // Display the randomly generated array
    cout << "Randomly generated array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Measure the time taken for sorting
    auto start = chrono::high_resolution_clock::now();
    quickSort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();

    // Calculate and display sorting time in microseconds
    chrono::duration<double, micro> duration = end - start;
    cout << "Time taken to sort the array: " << duration.count() << " microseconds" << endl;

    // Display the sorted array
    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
