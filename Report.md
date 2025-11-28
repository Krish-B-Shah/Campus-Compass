# Campus Compass Project Report

**Author:** [Your Name Here]  
**Date:** [Current Date]  
**Project:** Campus Compass - Student and Campus Navigation Management System

---

## 1. Project Overview

The Campus Compass project is a C++ application designed to help students at the University of Florida manage their class schedules and navigate campus efficiently. The system handles student information, class management, and calculates optimal routes between campus locations, accounting for road closures due to construction.

### Key Features:
- Student registration and management
- Class enrollment and scheduling
- Campus graph representation with edge management
- Shortest path calculations using Dijkstra's algorithm
- Minimum Spanning Tree (MST) calculation for student zones
- Schedule verification (extra credit)

---

## 2. Architecture and Design

### 2.1 Class Structure

The project is organized into four main classes:

#### **Graph Class** (`Graph.h`, `Graph.cpp`)
- **Purpose:** Represents the campus as an undirected graph
- **Data Structure:** `unordered_map<int, vector<Edge>>` adjacency list
- **Key Methods:**
  - `insert_edge()`: Adds bidirectional edges to the graph
  - `toggleEdgeClosure()`: Opens/closes edges for construction
  - `checkEdgeStatus()`: Returns edge status (open/closed/DNE)
  - `isConnected()`: BFS-based connectivity check
  - `shortestPath()`: Dijkstra's algorithm for shortest path
  - `calculateMST()`: Kruskal's algorithm for MST calculation

#### **StudentManager Class** (`StudentManager.h`, `StudentManager.cpp`)
- **Purpose:** Manages student data and class enrollments
- **Data Structure:** `unordered_map<int, Student>` for O(1) student lookup
- **Key Methods:**
  - `insertStudent()`: Validates and adds students
  - `removeStudent()`: Removes students by ID
  - `dropClass()`: Removes a class from a student
  - `replaceClass()`: Replaces one class with another
  - `removeClassFromAll()`: Removes a class from all students
  - Validation methods for UFID, names, and class codes

#### **CommandProcessor Class** (`CommandProcessor.h`, `CommandProcessor.cpp`)
- **Purpose:** Parses and executes user commands
- **Responsibilities:**
  - Command parsing and tokenization
  - Quoted name parsing
  - Routing commands to appropriate handlers
  - Class-to-location mapping
  - Exception-safe integer parsing

#### **CampusCompass Class** (`CampusCompass.h`, `CampusCompass.cpp`)
- **Purpose:** Main application controller
- **Responsibilities:**
  - CSV file parsing (edges.csv and classes.csv)
  - Command processing delegation
  - Initialization and coordination

---

## 3. Data Structures and Algorithms

### 3.1 Graph Representation
- **Type:** Undirected weighted graph
- **Implementation:** Adjacency list using `unordered_map<int, vector<Edge>>`
- **Edge Structure:**
  ```cpp
  struct Edge {
      int to;                    // Destination vertex
      int weight;                // Travel time
      bool closed_for_construction; // Edge status
  };
  ```

### 3.2 Shortest Path Algorithm
- **Algorithm:** Dijkstra's algorithm with priority queue
- **Time Complexity:** O((V + E) log V)
- **Features:**
  - Path reconstruction
  - Handles closed edges
  - Returns -1 for unreachable destinations

### 3.3 Minimum Spanning Tree
- **Algorithm:** Kruskal's algorithm with Union-Find
- **Time Complexity:** O(E log E)
- **Purpose:** Calculate student zone cost
- **Implementation:** Sorts edges by weight, uses Union-Find to avoid cycles

### 3.4 Connectivity Check
- **Algorithm:** Breadth-First Search (BFS)
- **Time Complexity:** O(V + E)
- **Purpose:** Verify if two locations are connected via open edges

---

## 4. Command Implementation

### 4.1 Student Management Commands

#### `insert STUDENT_NAME STUDENT_ID RESIDENCE_LOCATION_ID N CLASSCODE_1 ... CLASSCODE_N`
- Validates UFID (8 digits), name (letters and spaces only)
- Validates class codes (3 uppercase letters + 4 digits)
- Ensures 1-6 classes per student
- Stores student in hash map for O(1) access

#### `remove STUDENT_ID`
- O(1) lookup and removal
- Returns "unsuccessful" if student doesn't exist

#### `dropClass STUDENT_ID CLASSCODE`
- Removes class from student's schedule
- Automatically removes student if they have 0 classes remaining

#### `replaceClass STUDENT_ID CLASSCODE_1 CLASSCODE_2`
- Validates new class code format
- Ensures student doesn't already have new class
- Replaces old class with new class

#### `removeClass CLASSCODE`
- Iterates through all students
- Removes class from each student's schedule
- Removes students with 0 classes
- Returns count of affected students

### 4.2 Graph Operation Commands

#### `toggleEdgesClosure N LOCATION_ID_X LOCATION_ID_Y ...`
- Toggles closure status of N edge pairs
- Bidirectional edge handling
- Updates edge status in graph

#### `checkEdgeStatus LOCATION_ID_X LOCATION_ID_Y`
- Checks if edge exists and its status
- Returns "open", "closed", or "DNE"

#### `isConnected LOCATION_ID_1 LOCATION_ID_2`
- Uses BFS to check connectivity
- Only considers open edges
- Returns "successful" or "unsuccessful"

### 4.3 Path Finding Commands

#### `printShortestEdges ID`
- Gets student's residence and classes
- Calculates shortest path to each class
- Sorts classes lexicographically
- Prints time or -1 if unreachable

#### `printStudentZone ID`
- Finds shortest paths to all classes
- Collects all vertices from paths
- Calculates MST of subgraph
- Returns total MST cost

### 4.4 Extra Credit: `verifySchedule ID`
- Retrieves class times from CSV data
- Sorts classes by start time
- Calculates time gaps between consecutive classes
- Compares gaps with shortest path travel times
- Determines schedule feasibility

---

## 5. Data Validation

### 5.1 UFID Validation
- Must be exactly 8 digits
- Must be unique (checked before insertion)
- Range: 10000000 to 99999999

### 5.2 Name Validation
- Only letters (a-z, A-Z) and spaces allowed
- Cannot be empty
- Handles quoted names with spaces

### 5.3 Class Code Validation
- Format: 3 uppercase letters + 4 digits
- Example: COP3502, MAC2311
- Total length: exactly 7 characters

### 5.4 Class Count Validation
- Minimum: 1 class
- Maximum: 6 classes
- Must match number of class codes provided

---

## 6. CSV Parsing

### 6.1 edges.csv Format
```
LocationID_1,LocationID_2,Name_1,Name_2,Time
```
- Parses bidirectional edges
- Creates edges in both directions
- Stores edge weights (travel time)
- Initial status: all edges open

### 6.2 classes.csv Format
```
ClassCode,LocationID,Start Time (HH:MM),End Time (HH:MM)
```
- Maps class codes to location IDs
- Stores class times for schedule verification
- Populates class-to-location mapping

---

## 7. Error Handling

### 7.1 Exception Safety
- All `stoi()` calls wrapped in try-catch
- `safeStoi()` helper function prevents crashes
- Invalid input returns "unsuccessful"

### 7.2 Input Validation
- Token count validation
- Type checking before parsing
- Format validation for all inputs

### 7.3 Edge Cases Handled
- Empty input
- Missing tokens
- Invalid command names
- Non-existent students/classes
- Duplicate entries

---

## 8. Testing Strategy

### 8.1 Unit Tests
Five comprehensive test cases covering:

1. **Invalid Commands Test:** Tests five different types of invalid inputs
2. **Edge Cases Test:** Tests removal of non-existent entities
3. **CRUD Operations Test:** Tests dropClass, removeClass, remove, replaceClass
4. **Shortest Path with Edge Closure:** Tests path calculation before/after edge closure
5. **Integration Test:** Tests multiple commands together

### 8.2 Test Coverage
- Input validation
- Student management operations
- Graph operations
- Path finding algorithms
- Edge case scenarios

---

## 9. Complexity Analysis

### 9.1 Time Complexities
- **Insert Student:** O(N) where N = number of classes
- **Remove Student:** O(1) average case
- **Drop Class:** O(M) where M = classes per student (max 6)
- **Shortest Path:** O((V + E) log V)
- **MST Calculation:** O(E log E)
- **Connectivity Check:** O(V + E)

### 9.2 Space Complexities
- **Graph Storage:** O(V + E)
- **Student Storage:** O(S) where S = number of students
- **Class Mapping:** O(C) where C = number of classes

---

## 10. Challenges and Solutions

### 10.1 Challenge: Quoted Name Parsing
**Solution:** Implemented custom `parseQuotedName()` function that handles quoted strings with spaces correctly.

### 10.2 Challenge: Bidirectional Edges
**Solution:** When parsing edges.csv, create edges in both directions to maintain undirected graph property.

### 10.3 Challenge: Class-to-Location Mapping
**Solution:** Created `classToLocation` map in CommandProcessor, populated during CSV parsing.

### 10.4 Challenge: MST Calculation
**Solution:** Implemented Kruskal's algorithm with Union-Find data structure for efficient MST calculation.

### 10.5 Challenge: Exception Safety
**Solution:** Created `safeStoi()` wrapper function to handle all integer parsing safely.

---

## 11. Future Improvements

1. **Caching:** Cache shortest paths for frequently accessed routes
2. **Optimization:** Use A* algorithm for faster pathfinding
3. **UI:** Add graphical interface for better user experience
4. **Real-time Updates:** Support for dynamic edge closure updates
5. **Analytics:** Track most used paths and optimize accordingly

---

## 12. Conclusion

The Campus Compass project successfully implements a comprehensive student and campus navigation management system. All required features have been implemented, including:

- Complete student management system
- Graph-based campus representation
- Efficient pathfinding algorithms
- Robust error handling and validation
- Comprehensive test coverage

The system is production-ready and handles all edge cases appropriately. The modular design allows for easy maintenance and future enhancements.

---

## Appendix A: File Structure

```
Campus-Compass/
├── src/
│   ├── main.cpp
│   ├── CampusCompass.h/cpp
│   ├── Graph.h/cpp
│   ├── StudentManager.h/cpp
│   └── CommandProcessor.h/cpp
├── data/
│   ├── edges.csv
│   └── classes.csv
├── test/
│   └── test.cpp
└── CMakeLists.txt
```

## Appendix B: Key Algorithms Used

1. **Dijkstra's Algorithm:** Shortest path calculation
2. **Kruskal's Algorithm:** Minimum Spanning Tree
3. **Breadth-First Search:** Connectivity checking
4. **Union-Find:** Cycle detection in MST

---

**End of Report**

