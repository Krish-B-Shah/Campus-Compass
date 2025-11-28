# include "Graph.h"
#include <iostream> 

using namespace std; 


graph::graph(){

}

int graph::count_connected_edge(int ID){
    if (adj.find(ID) == adj.end()){
        return 0; 
    }
    return adj[ID].size(); 
}

void graph::insert_edge(int id, Edge e){
    adj[id].push_back(e); 
}