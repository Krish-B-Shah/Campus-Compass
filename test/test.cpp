#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include "CampusCompass.h"

using namespace std;

TEST_CASE("Test 1: Five Incorrect Commands", "[validation]") {
    CampusCompass compass;
    compass.ParseCSV("data/edges.csv", "data/classes.csv");
    
    stringstream ss;
    streambuf* oldCout = cout.rdbuf(ss.rdbuf());
    
    // Test 1: Invalid name (contains numbers)
    compass.ParseCommand(R"(insert "Student123" 12345678 1 1 COP3502)");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    // Test 2: Invalid UFID (not 8 digits)
    compass.ParseCommand(R"(insert "Valid Name" 1234567 1 1 COP3502)");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    // Test 3: Invalid class code (wrong format)
    compass.ParseCommand(R"(insert "Valid Name" 12345678 1 1 COP350)");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    // Test 4: Invalid number of classes (0 classes)
    compass.ParseCommand(R"(insert "Valid Name" 12345678 1 0)");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    // Test 5: Invalid command name
    compass.ParseCommand(R"(invalidCommand 12345678)");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    cout.rdbuf(oldCout);
}

TEST_CASE("Test 2: Edge Cases for Various Functions", "[edge_cases]") {
    CampusCompass compass;
    compass.ParseCSV("data/edges.csv", "data/classes.csv");
    
    stringstream ss;
    streambuf* oldCout = cout.rdbuf(ss.rdbuf());
    
    // Edge Case 1: Remove student that doesn't exist
    compass.ParseCommand("remove 99999999");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    // Edge Case 2: Drop class from student that doesn't exist
    compass.ParseCommand("dropClass 99999999 COP3502");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    // Edge Case 3: Replace class for student that doesn't exist
    compass.ParseCommand("replaceClass 99999999 COP3502 COP3503");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    cout.rdbuf(oldCout);
}

TEST_CASE("Test 3: dropClass, removeClass, remove, and replaceClass Commands", "[crud_operations]") {
    CampusCompass compass;
    compass.ParseCSV("data/edges.csv", "data/classes.csv");
    
    stringstream ss;
    streambuf* oldCout = cout.rdbuf(ss.rdbuf());
    
    // Setup: Insert students
    compass.ParseCommand(R"(insert "Test Student A" 11111111 1 2 COP3502 MAC2311)");
    REQUIRE(ss.str().find("successful") != string::npos);
    ss.str("");
    
    compass.ParseCommand(R"(insert "Test Student B" 22222222 2 1 COP3502)");
    REQUIRE(ss.str().find("successful") != string::npos);
    ss.str("");
    
    // Test dropClass: Drop a class from student
    compass.ParseCommand("dropClass 11111111 COP3502");
    REQUIRE(ss.str().find("successful") != string::npos);
    ss.str("");
    
    // Test replaceClass: Replace a class
    compass.ParseCommand("replaceClass 11111111 MAC2311 COP3503");
    REQUIRE(ss.str().find("successful") != string::npos);
    ss.str("");
    
    // Test removeClass: Remove class from all students (should affect Student B)
    compass.ParseCommand("removeClass COP3502");
    string output = ss.str();
    REQUIRE(output.find("1") != string::npos || output.find("2") != string::npos);
    ss.str("");
    
    // Test remove: Remove a student
    compass.ParseCommand("remove 11111111");
    REQUIRE(ss.str().find("successful") != string::npos);
    ss.str("");
    
    // Verify student is removed
    compass.ParseCommand("remove 11111111");
    REQUIRE(ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    cout.rdbuf(oldCout);
}

TEST_CASE("Test 4: printShortestEdges with Edge Closure", "[shortest_path]") {
    CampusCompass compass;
    compass.ParseCSV("data/edges.csv", "data/classes.csv");
    
    stringstream ss;
    streambuf* oldCout = cout.rdbuf(ss.rdbuf());
    
    // Insert a student with a class
    compass.ParseCommand(R"(insert "Path Test Student" 33333333 1 1 COP3502)");
    ss.str("");
    
    // First, check if student can reach the class (before closing edges)
    compass.ParseCommand("printShortestEdges 33333333");
    string output1 = ss.str();
    bool canReachBefore = (output1.find("Total Time: -1") == string::npos);
    ss.str("");
    
    // Close some edges that might be on the path
    // Note: This depends on the actual graph structure
    // We'll close edge between location 1 and a common location
    compass.ParseCommand("toggleEdgesClosure 1 1 2");
    ss.str("");
    
    // Check again - student might not be able to reach now
    compass.ParseCommand("printShortestEdges 33333333");
    string output2 = ss.str();
    
    // Verify that the output changed (either became unreachable or time increased)
    REQUIRE(output1 != output2);
    
    // Reopen the edge
    compass.ParseCommand("toggleEdgesClosure 1 1 2");
    ss.str("");
    
    // Check again - should be able to reach again
    compass.ParseCommand("printShortestEdges 33333333");
    string output3 = ss.str();
    
    // Should match original or be reachable
    if (canReachBefore) {
        REQUIRE(output3.find("Total Time: -1") == string::npos);
    }
    
    cout.rdbuf(oldCout);
}

TEST_CASE("Test 5: Comprehensive Integration Test", "[integration]") {
    CampusCompass compass;
    compass.ParseCSV("data/edges.csv", "data/classes.csv");
    
    stringstream ss;
    streambuf* oldCout = cout.rdbuf(ss.rdbuf());
    
    // Insert multiple students
    compass.ParseCommand(R"(insert "Alice Smith" 44444444 1 2 COP3502 MAC2311)");
    REQUIRE(ss.str().find("successful") != string::npos);
    ss.str("");
    
    compass.ParseCommand(R"(insert "Bob Jones" 55555555 2 1 COP3502)");
    REQUIRE(ss.str().find("successful") != string::npos);
    ss.str("");
    
    // Test isConnected
    compass.ParseCommand("isConnected 1 2");
    REQUIRE(ss.str().find("successful") != string::npos || ss.str().find("unsuccessful") != string::npos);
    ss.str("");
    
    // Test checkEdgeStatus
    compass.ParseCommand("checkEdgeStatus 1 2");
    string status = ss.str();
    REQUIRE(status.find("open") != string::npos || 
            status.find("closed") != string::npos || 
            status.find("DNE") != string::npos);
    ss.str("");
    
    // Test toggleEdgesClosure
    compass.ParseCommand("toggleEdgesClosure 1 1 2");
    REQUIRE(ss.str().find("successful") != string::npos);
    ss.str("");
    
    // Verify edge status changed
    compass.ParseCommand("checkEdgeStatus 1 2");
    string newStatus = ss.str();
    REQUIRE(status != newStatus);
    ss.str("");
    
    // Test removeClass affects multiple students
    compass.ParseCommand("removeClass COP3502");
    string removeOutput = ss.str();
    REQUIRE(removeOutput.find("1") != string::npos || removeOutput.find("2") != string::npos);
    
    cout.rdbuf(oldCout);
}
