#pragma once
#include <iostream> 
#include <unordered_map>
#include <vector>
using namespace std; 


// USE struct so we can avoid any private and public declaration.

struct Edge{
    int to; // To what point is going to 
    int weight; // How much time it will take from going from this point to next point. 0
    bool closed_for_construction; // Checks whether its closed for the constrcution or its not. 
};

class Graph{
    private: 
        unordered_map<int, vector<Edge>> adj;
    public: 
        Graph();
        int count_connected_edge(int ID); 
        void insert_edge(int id, Edge e);
        void toggleEdgeClosure(int from, int to);
        string checkEdgeStatus(int from, int to);
        bool isConnected(int from, int to);
        int shortestPath(int from, int to, vector<int>& path);
        int calculateMST(const vector<int>& vertices);
};

