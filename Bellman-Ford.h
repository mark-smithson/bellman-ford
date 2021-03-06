#pragma once

#include <iostream>
#include <limits>
#include <vector>
using namespace std;

using Arc = pair<double,int>; //the double is the weight of the arc for some u-v
using Graph = vector<vector<Arc>>;

const double infinite = numeric_limits<int>::max();

void print_path (int xi, int xf, const vector<int> &prev) {
    if (xf == xi) cout << xi;
    else {
        print_path(xi , prev[xf], prev);
        cout << " " << xf;
    }
}

void Bellman_Ford(const Graph& G, int start, int end) {
    int V = G.size();

    vector<int> prev(V);
    vector<int> dist(V, infinite);

    dist[start] = 0;

    for (int i = 0; i < V; ++i) {

        for (int j = 0; j < V; ++j) {
            for (Arc a : G[j]) {
                int v = a.second;
                double weight = a.first;

                if (dist[v] > dist[j] + weight) {
                    dist[v] = dist[j] + weight;
                    prev[v] = j;
                }
            }
        }
    }

    print_path(start,end,prev);
    cout << endl;
}