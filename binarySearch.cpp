#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int> &arr, int target)
{
    int start = 0;
    int end = arr.size() - 1;
    int mid;

    while (start <= end)
    {
        mid = start + (end - start) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }
        else if (arr[mid] < target)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }

    return -1;
}

int main()
{
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> arr(size);

    srand(time(0));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10000; 
    }
    sort(arr.begin(), arr.end()); 

    cout << "The randomly generated sorted array is: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    int target = arr[rand() % size];
    cout << "Randomly chosen target element: " << target << endl;

    int iterations = 100000; 

    long long totalTime = 0;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++)
    {
        binarySearch(arr, target);
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    totalTime = duration.count();

    cout << "The target element is: " << target << endl;
    cout << "Total time taken for " << iterations << " iterations: " << totalTime << " nanoseconds" << endl;
    cout << "Average time per iteration: " << (totalTime / iterations) << " nanoseconds" << endl;

    return 0;
}

