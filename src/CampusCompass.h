#pragma once
#include <string>
#include "StudentManager.h"
#include "Graph.h"
#include "CommandProcessor.h"
using namespace std;

class CampusCompass {
private:
    Graph graph; 
    StudentManager students; 
    CommandProcessor commands; 

public:
    CampusCompass();
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool ParseCommand(const string &command);
};
