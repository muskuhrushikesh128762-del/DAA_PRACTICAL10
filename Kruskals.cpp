#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

// Find the parent of a node
int findParent(int node, vector<int>& parent) {
    if (parent[node] == node)
        return node;

    return parent[node] = findParent(parent[node], parent);
}

// Union two sets
void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
    u = findParent(u, parent);
    v = findParent(v, parent);

    if (u != v) {
        if (rank[u] < rank[v])
            swap(u, v);

        parent[v] = u;

        if (rank[u] == rank[v])
            rank[u]++;
    }
}

int main() {
    int V = 5;

    vector<Edge> edges = {
        {0, 1, 2},
        {0, 3, 6},
        {1, 2, 3},
        {1, 3, 8},
        {1, 4, 5},
        {2, 4, 7},
        {3, 4, 9}
    };

    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    vector<int> parent(V);
    vector<int> rank(V, 0);

    // Initially, every vertex is its own parent
    for (int i = 0; i < V; i++)
        parent[i] = i;

    int totalWeight = 0;

    cout << "Edges in MST:\n";

    for (Edge edge : edges) {
        int u = edge.u;
        int v = edge.v;

        // Check if adding this edge creates a cycle
        if (findParent(u, parent) != findParent(v, parent)) {
            cout << u << " - " << v << " : " << edge.weight << endl;

            totalWeight += edge.weight;
            unionSet(u, v, parent, rank);
        }
    }

    cout << "Total weight = " << totalWeight << endl;

    return 0;
}
