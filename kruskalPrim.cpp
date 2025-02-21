#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Structure to represent an edge
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// Comparator for sorting edges by weight
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Disjoint Set Union (DSU) for Kruskal's Algorithm
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Kruskal's Algorithm
void kruskal(int n, vector<Edge>& edges) {
    cout << "Input Graph (Edge List):" << endl;
    for (auto& edge : edges) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }

    sort(edges.begin(), edges.end(), compare);

    DSU dsu(n);
    int mstWeight = 0;
    cout << "\nKruskal's MST Edges:" << endl;

    for (auto& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
            mstWeight += edge.weight;
        } else {
            cout << "Discarded (Cycle Formation): " << edge.u << " - " << edge.v << " : " << edge.weight << endl;
        }
    }

    cout << "Total Weight of Kruskal's MST: " << mstWeight << "\n" << endl;
}

// Prim's Algorithm
void prim(int n, vector<vector<pair<int, int>>>& adj) {
    cout << "Input Graph (Adjacency List):" << endl;
    for (int i = 0; i < n; i++) {
        cout << i << " -> ";
        for (auto& edge : adj[i]) {
            cout << "(" << edge.first << ", " << edge.second << ") ";
        }
        cout << endl;
    }

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
    vector<bool> inMST(n, false);

    pq.push({0, {0, -1}});
    int mstWeight = 0;

    cout << "\nPrim's MST Edges:" << endl;

    while (!pq.empty()) {
        auto current = pq.top();
        pq.pop();

        int weight = current.first;
        int u = current.second.first;
        int parent = current.second.second;

        if (inMST[u]) {
            cout << "Discarded (Cycle Formation): " << parent << " - " << u << " : " << weight << endl;
            continue;
        }

        inMST[u] = true;
        if (parent != -1) {
            cout << parent << " - " << u << " : " << weight << endl;
            mstWeight += weight;
        }

        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int w = neighbor.second;
            if (!inMST[v]) {
                pq.push({w, {v, u}});
            }
        }
    }

    cout << "Total Weight of Prim's MST: " << mstWeight << "\n" << endl;
}

int main() {
    int n = 7;
    vector<Edge> edges = {
        {0, 1, 7}, {0, 3, 5}, {1, 2, 8}, {1, 3, 9}, {1, 4, 7},
        {2, 4, 5}, {3, 4, 15}, {3, 5, 6}, {4, 5, 8}, {4, 6, 9}, {5, 6, 11}
    };

    vector<vector<pair<int, int>>> adj(n);
    for (auto& edge : edges) {
        adj[edge.u].push_back({edge.v, edge.weight});
        adj[edge.v].push_back({edge.u, edge.weight});
    }

    kruskal(n, edges);
    prim(n, adj);

    return 0;
}