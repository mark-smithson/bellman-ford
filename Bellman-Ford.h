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

void result (int xi, int xf, const vector<int> &prev, vector<int> &res) {
    if (xf == xi) res.push_back(xi);
    else {
        result(xi,prev[xf],prev,res);
        res.push_back(xf);
    }
}

/* Given two nodes it computes the shortest path between them.
    The graph cannot contain any negative cycle */
vector<int> Bellman_Ford(const Graph& G, int start, int end) {
    int V = G.size();
    
    vector<int> res;
    vector<int> prev(V);
    vector<int> dist(V, infinite);

    dist[start] = 0;
    bool mod = false;

    for (int i = 0; i < V; ++i) {
        
        for (int j = 0; j < V; ++j) {
            for (Arc a : G[j]) {
                int node = a.second;
                double weight = a.first;

                if (dist[node] > dist[j] + weight) {
                    mod = true;
                    dist[node] = dist[j] + weight;
                    prev[node] = j;
                }
            }
        }

        if (not mod) {
            result(start,end,prev,res);
            return res;
        }

        mod = false;
    }
    
    result(start,end,prev,res);
    return res;
}
