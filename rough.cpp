#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

typedef pair<int, int> pii;

// Dijkstra's Algorithm
void dijkstra(vector<vector<pii>> &graph, int src, int V) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

// Function to generate a random weighted graph
vector<vector<pii>> generateGraph(int V, double density = 0.3) {
    vector<vector<pii>> graph(V);
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if ((double)rand() / RAND_MAX < density) {  // Edge probability
                int weight = rand() % 20 + 1;  // Random weight between 1-20
                graph[i].push_back({j, weight});
                graph[j].push_back({i, weight});
            }
        }
    }
    return graph;
}

int main() {
    srand(time(0));  // Seed for random numbers
    vector<int> sizes = {10, 50, 100, 200, 500, 1000};  // Different graph sizes

    cout << "Dijkstra Execution Time for Different Input Sizes:\n";
    cout << "---------------------------------------------------\n";
    cout << "Nodes (V) | Execution Time (ms)\n";
    cout << "---------------------------------\n";

    for (int V : sizes) {
        vector<vector<pii>> graph = generateGraph(V, 0.3);
        
        auto start = high_resolution_clock::now();
        dijkstra(graph, 0, V);  // Run Dijkstra from source 0
        auto stop = high_resolution_clock::now();
        
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << V << "        | " << duration.count() << " ms\n";
    }

    return 0;
}
