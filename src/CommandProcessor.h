#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class StudentManager;
class Graph;

class CommandProcessor {
private:
    StudentManager& studentManager;
    Graph& campusGraph;
    std::unordered_map<std::string, int> classToLocation;

public:
    CommandProcessor(StudentManager& sm, Graph& g);

    void processCommand(const std::string& commandLine);
    void setClassLocation(const std::string& classCode, int locationID);
    void setClassTime(const std::string& classCode, int startHour, int startMinute, int endHour, int endMinute);

private:
    std::vector<std::string> parseQuotedName(const std::string& commandLine, size_t& pos);
    int getClassLocation(const std::string& classCode);
    bool safeStoi(const std::string& str, int& result);
    void handleInsert(const std::vector<std::string>& tokens);
    void handleRemove(const std::vector<std::string>& tokens);
    void handleDropClass(const std::vector<std::string>& tokens);
    void handleReplaceClass(const std::vector<std::string>& tokens);
    void handleRemoveClass(const std::vector<std::string>& tokens);
    void handleToggleEdges(const std::vector<std::string>& tokens);
    void handleCheckEdgeStatus(const std::vector<std::string>& tokens);
    void handleIsConnected(const std::vector<std::string>& tokens);
    void handlePrintShortestEdges(const std::vector<std::string>& tokens);
    void handlePrintStudentZone(const std::vector<std::string>& tokens);
    void handleVerifySchedule(const std::vector<std::string>& tokens);
    
    struct ClassTime {
        int startHour;
        int startMinute;
        int endHour;
        int endMinute;
    };
    std::unordered_map<std::string, ClassTime> classTimes;
};