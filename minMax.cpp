#include <bits/stdc++.h>
using namespace std;

vector<int> minMax(vector<int> &arr)
{
    vector<int> ans;
    int n = arr.size();
    int mini;
    int maxi;
    int i;

    if (n % 2 != 0)
    {
        mini = arr[0];
        maxi = arr[0];
        i = 1;
    }
    else
    {
        if (arr[0] < arr[1])
        {
            mini = arr[0];
            maxi = arr[1];
        }
        else
        {
            mini = arr[1];
            maxi = arr[0];
        }
        i = 2;
    }

    while (i < n - 1)
    {
        if (arr[i] < arr[i + 1])
        {
            mini = min(mini, arr[i]);
            maxi = max(maxi, arr[i + 1]);
        }
        else
        {
            mini = min(mini, arr[i + 1]);
            maxi = max(maxi, arr[i]);
        }
        i = i + 2;
    }

    ans.push_back(mini);
    ans.push_back(maxi);

    return ans;
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

    int iterations = (size < 10) ? 100000 : 1000;

    auto start = chrono::high_resolution_clock::now();
    vector<int> result;
    for (int i = 0; i < iterations; i++)
    {
        random_shuffle(arr.begin(), arr.end()); 
        result = minMax(arr);
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cout << "The randomly generated array is: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "Minimum element in the given array is: " << result[0] << endl;
    cout << "Maximum element in the given array is: " << result[1] << endl;

    cout << "Average time taken by minMax function: " << (duration.count() / iterations) << " nanoseconds" << endl;

    return 0;
}

