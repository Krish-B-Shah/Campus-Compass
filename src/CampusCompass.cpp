#include "CampusCompass.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

using namespace std;

CampusCompass::CampusCompass() : commands(students, graph) {
}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    ifstream edgesFile(edges_filepath);
    if (!edgesFile.is_open()) {
        return false;
    }
    
    string line;
    getline(edgesFile, line);
    
    while (getline(edgesFile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 5) {
            try {
                int from = stoi(tokens[0]);
                int to = stoi(tokens[1]);
                int weight = stoi(tokens[4]);
                
                Edge e1 = {to, weight, false};
                Edge e2 = {from, weight, false};
                
                graph.insert_edge(from, e1);
                graph.insert_edge(to, e2);
            } catch (const invalid_argument& e) {
                continue;
            } catch (const out_of_range& e) {
                continue;
            }
        }
    }
    edgesFile.close();
    
    ifstream classesFile(classes_filepath);
    if (!classesFile.is_open()) {
        return false;
    }
    
    getline(classesFile, line);
    
    while (getline(classesFile, line)) {
        if (line.empty()) continue;
        
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 4) {
            try {
                string classCode = tokens[0];
                int locationID = stoi(tokens[1]);
                commands.setClassLocation(classCode, locationID);
                
                string startTime = tokens[2];
                string endTime = tokens[3];
                
                size_t colonPos = startTime.find(':');
                if (colonPos != string::npos) {
                    int startHour = stoi(startTime.substr(0, colonPos));
                    int startMinute = stoi(startTime.substr(colonPos + 1));
                    
                    colonPos = endTime.find(':');
                    if (colonPos != string::npos) {
                        int endHour = stoi(endTime.substr(0, colonPos));
                        int endMinute = stoi(endTime.substr(colonPos + 1));
                        
                        commands.setClassTime(classCode, startHour, startMinute, endHour, endMinute);
                    }
                }
            } catch (const invalid_argument& e) {
                continue;
            } catch (const out_of_range& e) {
                continue;
            }
        }
    }
    classesFile.close();
    
    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    commands.processCommand(command);
    return true;
}
