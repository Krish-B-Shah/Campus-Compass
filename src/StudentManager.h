#pragma once
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Student{
    string student_name; 
    int id; 
    int residence_location_id; 
    vector<string> classes; 
};

class StudentManager {
private: 
    unordered_map<int, Student> students; 

public:
    StudentManager() = default; 
    bool insertStudent(string& name, int id, int residenceID, vector<string>& classCodes);
    bool removeStudent(int id);
    bool dropClass(int id, const string& classCode);
    bool replaceClass(int id, const string& oldCode, const string& newCode);
    int removeClassFromAll(const string& classCode);
    bool isValidName(const string& name);
    bool isValidClassCode(const string& classCode);
    bool isValidID(int id);
    bool isValidUFID(int id);
    bool getStudent(int id, Student& student) const; 
};

