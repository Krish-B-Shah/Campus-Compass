#include <iostream>

#include "CampusCompass.h"

using namespace std;

int main() {

    Graph g; 

    
    Edge e1 = {2, 10, false};
    Edge e2 = {4, 5, true};


    g.insert_edge(1, e1);
    g.insert_edge(1, e2);

    cout<< "Node 1 has " << g.count_connected_edge(1) << " edges \n"; 

    return 0; 


    // // initialize your main project object
    // CampusCompass compass;

    // // ingest CSV data
    // compass.ParseCSV("../data/edges.csv", "../data/classes.csv");

    // // the below is example code for parsing commandline input
    // int no_of_lines;
    // string command;
    // cin >> no_of_lines;
    // cin.ignore(); // ignore newline that first cin left over
    // for (int i = 0; i < no_of_lines; i++) {
    //     getline(cin, command);

    //     // parse your commands however you see fit
    //     compass.ParseCommand(command);
    // }
}
