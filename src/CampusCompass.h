#pragma once
#include <string>
#include "Graph.cpp"
#include "CommandProcessor.cpp"
#include "StudentManager.cpp"
using namespace std;

class CampusCompass {
private:
    // Think about what member variables you need to initialize
    // perhaps some graph representation?
public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseCommand(const string &command);
    Graph graph; 
    StudentManager students; 
    CommanProcessor commands; 
};
