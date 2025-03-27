#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

// Define a pair for (distance, node)
typedef pair<int, int> pii;

// Function to find the shortest paths from source to all vertices
void dijkstra(vector<vector<pii>> &graph, int src, int V) {
    vector<int> dist(V, INT_MAX); // Distance array initialized to infinity
    priority_queue<pii, vector<pii>, greater<pii>> pq; // Min-heap for priority queue

    // Start from the source node
    dist[src] = 0;
    pq.push({0, src}); // Push (distance, node)

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        // If the popped distance is greater, ignore it
        if (d > dist[u]) continue;

        // Traverse all adjacent vertices of u
        for (auto edge : graph[u]) {
            int v = edge.first;   // Destination node
            int weight = edge.second; // Edge weight

            // Relaxation step
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Display the input graph
    cout << "\nInput Graph:\n";
    cout << "Edge  |  Weight\n";
    for (int u = 0; u < V; u++) {
        for (auto edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (u < v) // To avoid duplicate printing in an undirected graph
                cout << u << " - " << v << "   |   " << weight << "\n";
        }
    }

    // Print the shortest distances from source
    cout << "\nShortest Distances from Source Vertex " << src << ":\n";
    cout << "Vertex  |  Distance\n";
    for (int i = 0; i < V; i++) {
        cout << i << "       |   " << dist[i] << "\n";
    }
}

// Driver function
int main() {
    int V = 5; // Number of vertices
    vector<vector<pii>> graph(V);

    // Manually adding edges based on the example graph
    graph[0].push_back({1, 2});
    graph[0].push_back({2, 4});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 1});
    graph[1].push_back({3, 7});
    graph[2].push_back({0, 4});
    graph[2].push_back({1, 1});
    graph[2].push_back({4, 3});
    graph[3].push_back({1, 7});
    graph[3].push_back({4, 1});
    graph[4].push_back({2, 3});
    graph[4].push_back({3, 1});

    int src = 0; // Source vertex

    // Call Dijkstra's Algorithm
    dijkstra(graph, src, V);

    return 0;
}

