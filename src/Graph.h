#include <iostream> 
#include <unordered_map>
#include <vector>
# pragma once
using namespace std; 


// USE struct so we can avoid any private and public declaration.

struct Edge{
    int to; // To what point is going to 
    int weight; // How much time it will take from going from this point to next point. 0
    bool closed_for_construction; // Checks whether its closed for the constrcution or its not. 
};

class graph{
    private: 
        unordered_map<int, vector<Edge>> adj; // this helps store each id with corresponding data. 
    public: 
        // SO there is a point what do we need to get? 
        // each point has unique ID. SO we need to count how many edges are there from a certain ID or point.
        int count_connected_edge(int ID); 
        void insert_edge(int id, Edge e); 
};

