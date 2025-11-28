#include "CommandProcessor.h"
#include "StudentManager.h"
#include "Graph.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <utility>

using namespace std;

CommandProcessor::CommandProcessor(StudentManager& sm, Graph& g) 
    : studentManager(sm), campusGraph(g) {
}

int CommandProcessor::getClassLocation(const string& classCode) {
    auto it = classToLocation.find(classCode);
    if (it != classToLocation.end()) {
        return it->second;
    }
    return -1;
}

void CommandProcessor::setClassLocation(const string& classCode, int locationID) {
    classToLocation[classCode] = locationID;
}

void CommandProcessor::setClassTime(const string& classCode, int startHour, int startMinute, int endHour, int endMinute) {
    ClassTime ct;
    ct.startHour = startHour;
    ct.startMinute = startMinute;
    ct.endHour = endHour;
    ct.endMinute = endMinute;
    classTimes[classCode] = ct;
}

bool CommandProcessor::safeStoi(const string& str, int& result) {
    try {
        result = stoi(str);
        return true;
    } catch (const invalid_argument& e) {
        return false;
    } catch (const out_of_range& e) {
        return false;
    }
}

vector<string> CommandProcessor::parseQuotedName(const string& commandLine, size_t& pos) {
    vector<string> result;
    while (pos < commandLine.length() && commandLine[pos] == ' ') pos++;
    
    if (pos >= commandLine.length() || commandLine[pos] != '"') {
        return result;
    }
    
    pos++;
    string name;
    while (pos < commandLine.length() && commandLine[pos] != '"') {
        name += commandLine[pos];
        pos++;
    }
    
    if (pos < commandLine.length()) pos++;
    result.push_back(name);
    return result;
}

void CommandProcessor::processCommand(const string& commandLine) {
    size_t pos = 0;
    vector<string> tokens;
    
    while (pos < commandLine.length()) {
        while (pos < commandLine.length() && commandLine[pos] == ' ') pos++;
        if (pos >= commandLine.length()) break;
        
        if (commandLine[pos] == '"') {
            vector<string> quoted = parseQuotedName(commandLine, pos);
            if (!quoted.empty()) {
                tokens.insert(tokens.end(), quoted.begin(), quoted.end());
            }
        } else {
            size_t start = pos;
            while (pos < commandLine.length() && commandLine[pos] != ' ') pos++;
            tokens.push_back(commandLine.substr(start, pos - start));
        }
    }
    
    if (tokens.empty()) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    string command = tokens[0];
    
    if (command == "insert") {
        handleInsert(tokens);
    } else if (command == "remove") {
        handleRemove(tokens);
    } else if (command == "dropClass") {
        handleDropClass(tokens);
    } else if (command == "replaceClass") {
        handleReplaceClass(tokens);
    } else if (command == "removeClass") {
        handleRemoveClass(tokens);
    } else if (command == "toggleEdgesClosure") {
        handleToggleEdges(tokens);
    } else if (command == "checkEdgeStatus") {
        handleCheckEdgeStatus(tokens);
    } else if (command == "isConnected") {
        handleIsConnected(tokens);
    } else if (command == "printShortestEdges") {
        handlePrintShortestEdges(tokens);
    } else if (command == "printStudentZone") {
        handlePrintStudentZone(tokens);
    } else if (command == "verifySchedule") {
        handleVerifySchedule(tokens);
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CommandProcessor::handleInsert(const vector<string>& tokens) {
    if (tokens.size() < 5) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    string name = tokens[1];
    int studentID, residenceID, N;
    
    if (!safeStoi(tokens[2], studentID) || 
        !safeStoi(tokens[3], residenceID) || 
        !safeStoi(tokens[4], N)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    if (tokens.size() != static_cast<size_t>(5 + N)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    vector<string> classCodes;
    for (int i = 0; i < N; i++) {
        classCodes.push_back(tokens[5 + i]);
    }
    
    if (studentManager.insertStudent(name, studentID, residenceID, classCodes)) {
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CommandProcessor::handleRemove(const vector<string>& tokens) {
    if (tokens.size() != 2) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int studentID;
    if (!safeStoi(tokens[1], studentID)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    if (studentManager.removeStudent(studentID)) {
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CommandProcessor::handleDropClass(const vector<string>& tokens) {
    if (tokens.size() != 3) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int studentID;
    if (!safeStoi(tokens[1], studentID)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    string classCode = tokens[2];
    
    if (studentManager.dropClass(studentID, classCode)) {
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CommandProcessor::handleReplaceClass(const vector<string>& tokens) {
    if (tokens.size() != 4) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int studentID;
    if (!safeStoi(tokens[1], studentID)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    string oldCode = tokens[2];
    string newCode = tokens[3];
    
    if (studentManager.replaceClass(studentID, oldCode, newCode)) {
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CommandProcessor::handleRemoveClass(const vector<string>& tokens) {
    if (tokens.size() != 2) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    string classCode = tokens[1];
    int count = studentManager.removeClassFromAll(classCode);
    cout << count << endl;
}

void CommandProcessor::handleToggleEdges(const vector<string>& tokens) {
    if (tokens.size() < 3 || (tokens.size() - 2) % 2 != 0) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int N;
    if (!safeStoi(tokens[1], N)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    if (tokens.size() != static_cast<size_t>(2 + N * 2)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    for (int i = 0; i < N; i++) {
        int from, to;
        if (!safeStoi(tokens[2 + i * 2], from) || 
            !safeStoi(tokens[3 + i * 2], to)) {
            cout << "unsuccessful" << endl;
            return;
        }
        campusGraph.toggleEdgeClosure(from, to);
    }
    
    cout << "successful" << endl;
}

void CommandProcessor::handleCheckEdgeStatus(const vector<string>& tokens) {
    if (tokens.size() != 3) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int from, to;
    if (!safeStoi(tokens[1], from) || !safeStoi(tokens[2], to)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    string status = campusGraph.checkEdgeStatus(from, to);
    cout << status << endl;
}

void CommandProcessor::handleIsConnected(const vector<string>& tokens) {
    if (tokens.size() != 3) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int from, to;
    if (!safeStoi(tokens[1], from) || !safeStoi(tokens[2], to)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    if (campusGraph.isConnected(from, to)) {
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}

void CommandProcessor::handlePrintShortestEdges(const vector<string>& tokens) {
    if (tokens.size() != 2) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int studentID;
    if (!safeStoi(tokens[1], studentID)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    Student student;
    if (!studentManager.getStudent(studentID, student)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    cout << "Name: " << student.student_name << endl;
    
    vector<string> sortedClasses = student.classes;
    sort(sortedClasses.begin(), sortedClasses.end());
    
    for (const string& classCode : sortedClasses) {
        int classLocation = getClassLocation(classCode);
        if (classLocation == -1) {
            cout << classCode << " | Total Time: -1" << endl;
            continue;
        }
        
        vector<int> path;
        int time = campusGraph.shortestPath(student.residence_location_id, classLocation, path);
        
        if (time == -1) {
            cout << classCode << " | Total Time: -1" << endl;
        } else {
            cout << classCode << " | Total Time: " << time << endl;
        }
    }
}

void CommandProcessor::handlePrintStudentZone(const vector<string>& tokens) {
    if (tokens.size() != 2) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int studentID;
    if (!safeStoi(tokens[1], studentID)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    Student student;
    if (!studentManager.getStudent(studentID, student)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    unordered_set<int> vertexSet;
    vertexSet.insert(student.residence_location_id);
    
    for (const string& classCode : student.classes) {
        int classLocation = getClassLocation(classCode);
        if (classLocation != -1) {
            vector<int> path;
            int time = campusGraph.shortestPath(student.residence_location_id, classLocation, path);
            if (time != -1) {
                for (int v : path) {
                    vertexSet.insert(v);
                }
            }
        }
    }
    
    vector<int> vertices(vertexSet.begin(), vertexSet.end());
    int mstCost = campusGraph.calculateMST(vertices);
    cout << "Student Zone Cost For " << student.student_name << ": " << mstCost << endl;
}

void CommandProcessor::handleVerifySchedule(const vector<string>& tokens) {
    if (tokens.size() != 2) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    int studentID;
    if (!safeStoi(tokens[1], studentID)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    Student student;
    if (!studentManager.getStudent(studentID, student)) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    if (student.classes.size() <= 1) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    vector<pair<string, ClassTime>> classesWithTimes;
    for (const string& classCode : student.classes) {
        auto it = classTimes.find(classCode);
        if (it != classTimes.end()) {
            classesWithTimes.push_back({classCode, it->second});
        }
    }
    
    if (classesWithTimes.empty()) {
        cout << "unsuccessful" << endl;
        return;
    }
    
    sort(classesWithTimes.begin(), classesWithTimes.end(), 
         [](const pair<string, ClassTime>& a, const pair<string, ClassTime>& b) {
             if (a.second.startHour != b.second.startHour) {
                 return a.second.startHour < b.second.startHour;
             }
             return a.second.startMinute < b.second.startMinute;
         });
    
    cout << "Schedule Check for " << student.student_name << ":" << endl;
    
    for (size_t i = 0; i < classesWithTimes.size() - 1; i++) {
        const string& class1 = classesWithTimes[i].first;
        const string& class2 = classesWithTimes[i + 1].first;
        const ClassTime& time1 = classesWithTimes[i].second;
        const ClassTime& time2 = classesWithTimes[i + 1].second;
        
        int endTime1 = time1.endHour * 60 + time1.endMinute;
        int startTime2 = time2.startHour * 60 + time2.startMinute;
        int timeGap = startTime2 - endTime1;
        
        int loc1 = getClassLocation(class1);
        int loc2 = getClassLocation(class2);
        
        if (loc1 == -1 || loc2 == -1) {
            cout << class1 << " - " << class2 << " Cannot make it!" << endl;
            continue;
        }
        
        vector<int> path;
        int travelTime = campusGraph.shortestPath(loc1, loc2, path);
        
        if (travelTime == -1) {
            cout << class1 << " - " << class2 << " Cannot make it!" << endl;
        } else if (timeGap >= travelTime) {
            cout << class1 << " - " << class2 << " Can make it!" << endl;
        } else {
            cout << class1 << " - " << class2 << " Cannot make it!" << endl;
        }
    }
}

