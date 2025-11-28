#include <string>
#include <vector>
#include "StudentManager.h"
#include <cctype>
#include <unordered_map>
#include <algorithm>
using namespace std; 

bool StudentManager::insertStudent(string& name, int id, int residenceID, vector<string>& classCodes){
    if (!isValidUFID(id)) {
        return false;
    }
    
    if (!isValidID(id)) {
        return false;
    }
    
    if (!isValidName(name)) {
        return false;
    }
    
    int N = classCodes.size();
    if (N < 1 || N > 6) {
        return false;
    }
    
    for (string& classCode : classCodes) {
        if (!isValidClassCode(classCode)) {
            return false;
        }
    }
    
    Student newStudent;
    newStudent.student_name = name;
    newStudent.id = id;
    newStudent.residence_location_id = residenceID;
    newStudent.classes = classCodes;
    
    students[id] = newStudent;
    
    return true;
}
bool StudentManager::removeStudent(int id){
    if (students.find(id) == students.end()) {
        return false;
    }
    
    students.erase(id);
    
    return true;
}
bool StudentManager::dropClass(int id, const string& classCode){
    if (students.find(id) == students.end()) {
        return false;
    }
    
    vector<string>& studentClasses = students[id].classes;
    
    auto it = find(studentClasses.begin(), studentClasses.end(), classCode);
    
    if (it == studentClasses.end()) {
        return false;
    }
    
    studentClasses.erase(it);
    
    if (studentClasses.empty()) {
        students.erase(id);
    }
    
    return true;
}
bool StudentManager::replaceClass(int id, const string& oldCode, const string& newCode){
    if (students.find(id) == students.end()) {
        return false;
    }
    
    if (!isValidClassCode(newCode)) {
        return false;
    }
    
    vector<string>& studentClasses = students[id].classes;
    
    if (find(studentClasses.begin(), studentClasses.end(), newCode) != studentClasses.end()) {
        return false;
    }
    
    auto it = find(studentClasses.begin(), studentClasses.end(), oldCode);
    
    if (it == studentClasses.end()) {
        return false;
    }
    
    *it = newCode;
    
    return true;
}
int  StudentManager::removeClassFromAll(const string& classCode){
    int count = 0;
    vector<int> studentsToRemove;
    
    for (auto& pair : students) {
        Student& student = pair.second;
        vector<string>& studentClasses = student.classes;
        
        auto it = find(studentClasses.begin(), studentClasses.end(), classCode);
        
        if (it != studentClasses.end()) {
            studentClasses.erase(it);
            count++;
            
            if (studentClasses.empty()) {
                studentsToRemove.push_back(pair.first);
            }
        }
    }
    
    for (int id : studentsToRemove) {
        students.erase(id);
    }
    
    return count;
}
bool StudentManager::isValidName(const string& name){
    if (name.empty()) {
        return false;
    }
    
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    
    return true;
}

bool StudentManager::isValidClassCode(const string& classCode) {
    if (classCode.length() != 7) {
        return false;
    }

    string sub_string1 = classCode.substr(0, 3);
    string sub_string2 = classCode.substr(3);

    for (char c : sub_string1) {
        if (!isupper(c)) {
            return false;
        }
    }

    for (char c : sub_string2) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}
bool StudentManager::isValidID(int id){
    if (!students.count(id)){
        return true; 
    }
    return false; 
}

bool StudentManager::isValidUFID(int id) {
    if (id < 10000000 || id > 99999999) {
        return false;
    }
    return true;
}

bool StudentManager::getStudent(int id, Student& student) const {
    auto it = students.find(id);
    if (it == students.end()) {
        return false;
    }
    student = it->second;
    return true;
}
    