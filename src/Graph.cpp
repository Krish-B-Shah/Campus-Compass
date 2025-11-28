#include "Graph.h"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <climits>

using namespace std; 

Graph::Graph(){

}

int Graph::count_connected_edge(int ID){
    if (adj.find(ID) == adj.end()){
        return 0; 
    }
    return adj[ID].size(); 
}

void Graph::insert_edge(int id, Edge e){
    adj[id].push_back(e); 
}

void Graph::toggleEdgeClosure(int from, int to) {
    if (adj.find(from) == adj.end()) {
        return;
    }
    
    for (Edge& e : adj[from]) {
        if (e.to == to) {
            e.closed_for_construction = !e.closed_for_construction;
            return;
        }
    }
}

string Graph::checkEdgeStatus(int from, int to) {
    if (adj.find(from) == adj.end()) {
        return "DNE";
    }
    
    for (const Edge& e : adj[from]) {
        if (e.to == to) {
            return e.closed_for_construction ? "closed" : "open";
        }
    }
    
    return "DNE";
}

bool Graph::isConnected(int from, int to) {
    if (from == to) return true;
    
    queue<int> q;
    unordered_set<int> visited;
    q.push(from);
    visited.insert(from);
    
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        
        if (adj.find(current) == adj.end()) {
            continue;
        }
        
        for (const Edge& e : adj[current]) {
            if (e.closed_for_construction) {
                continue;
            }
            
            if (e.to == to) {
                return true;
            }
            
            if (visited.find(e.to) == visited.end()) {
                visited.insert(e.to);
                q.push(e.to);
            }
        }
    }
    
    return false;
}

int Graph::shortestPath(int from, int to, vector<int>& path) {
    if (from == to) {
        path.push_back(from);
        return 0;
    }
    
    unordered_map<int, int> dist;
    unordered_map<int, int> parent;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[from] = 0;
    pq.push({0, from});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue;
        if (u == to) break;
        
        if (adj.find(u) == adj.end()) continue;
        
        for (const Edge& e : adj[u]) {
            if (e.closed_for_construction) continue;
            
            int v = e.to;
            int newDist = dist[u] + e.weight;
            
            if (dist.find(v) == dist.end() || newDist < dist[v]) {
                dist[v] = newDist;
                parent[v] = u;
                pq.push({newDist, v});
            }
        }
    }
    
    if (dist.find(to) == dist.end()) {
        return -1;
    }
    
    int current = to;
    while (current != from) {
        path.push_back(current);
        if (parent.find(current) == parent.end()) {
            return -1;
        }
        current = parent[current];
    }
    path.push_back(from);
    reverse(path.begin(), path.end());
    
    return dist[to];
}

int Graph::calculateMST(const vector<int>& vertices) {
    if (vertices.size() <= 1) return 0;
    
    unordered_set<int> vertexSet(vertices.begin(), vertices.end());
    
    vector<pair<int, pair<int, int>>> edges;
    for (int v : vertices) {
        if (adj.find(v) == adj.end()) continue;
        for (const Edge& e : adj[v]) {
            if (e.closed_for_construction) continue;
            if (vertexSet.find(e.to) != vertexSet.end()) {
                edges.push_back({e.weight, {v, e.to}});
            }
        }
    }
    
    sort(edges.begin(), edges.end());
    
    unordered_map<int, int> parent;
    for (int v : vertices) {
        parent[v] = v;
    }
    
    function<int(int)> find = [&](int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    int mstCost = 0;
    int edgesUsed = 0;
    
    for (const auto& edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int w = edge.first;
        
        int pu = find(u);
        int pv = find(v);
        
        if (pu != pv) {
            parent[pu] = pv;
            mstCost += w;
            edgesUsed++;
            if (edgesUsed == static_cast<int>(vertices.size()) - 1) break;
        }
    }
    
    return mstCost;
}