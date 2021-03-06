#pragma once

#include <iostream>
#include <limits>
#include <vector>
using namespace std;


/* This pair stores the information of an Arc. First atribute is the weight of the arc
and second atribute is the end node of the arc. */
using Arc = pair<double,int>; 

using Graph = vector<vector<Arc>>;

const double infinite = numeric_limits<int>::max();

/* This function writes the shortest path from xi to xf. */
void print_path (int xi, int xf, const vector<int> &prev) {
    if (xf == xi) cout << xi;
    else {
        print_path(xi , prev[xf], prev);
        cout << " " << xf;
    }
}

/* Given two nodes it compute the shortest path between them.
    The graph cannot contain any negative cycle.
    The graph is represented as an adjacency list*/
void Bellman_Ford(const Graph& G, int start, int end) {
    int V = G.size();

    vector<int> prev(V);
    vector<int> dist(V, infinite);

    dist[start] = 0;

    for (int i = 0; i < V; ++i) {

        for (int j = 0; j < V; ++j) {
            for (Arc a : G[j]) {
                int node = a.second;
                double weight = a.first;

                if (dist[node] > dist[j] + weight) {
                    dist[node] = dist[j] + weight;
                    prev[node] = j;
                }
            }
        }
    }

    print_path(start,end,prev);
    cout << endl;
}
