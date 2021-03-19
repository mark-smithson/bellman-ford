#pragma once

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
using namespace std;

/* This pair stores the information of an Arc. First atribute is the weight of the arc
and second atribute is the end node of the arc. */
using Arc = pair<double,int>; 


/* The indexes of the graph go from 0 to n-1. Being n the number of nodes of the graph*/
using Graph = vector<vector<Arc>>;

const double infinite = numeric_limits<int>::max();

/* This function computes the shortest path between two given nodes and returns
    a vector with the shortest path.
    The graph cannot contain any negative cycle. */
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

        //If no modification is made we can stop the algorithm.
        if (not mod) break;
        mod = false;
    }

    res.push_back(end);
    int aux = end;

    while (aux != start) {
        res.push_back(prev[aux]);
        aux = prev[aux];
    }

    reverse(res.begin(),res.end());
    return res;
}
