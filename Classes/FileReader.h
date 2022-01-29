
#ifndef BUS_SYSTEM_FILEREADER_H
#define BUS_SYSTEM_FILEREADER_H

#include "graph.h"

#include <map>

class FileReader {
    static string path;
    Graph* graph;
    unordered_map<string, int>* codeID; // codigo da parada e seu id
    unordered_map<string, string> codeNameOfLines; // codigo da linha e seu nome

    ///read the stops from stops.csv
    void readStops();
    ///put the stop read in line to the graph
    void readStop(const string& line, int id);
    ///read lines from lines.csv
    void readLines();
    ///put the line read to the unordered_map to be used later
    void readLine(const string &line);
    ///read the paths from the lines_code_0/1.csv
    void readPaths();
    ///put the path read to the graph's edges
    void readPath(const string& line, ifstream &file);
public:
    ///initialize the graph and the codeID variable with the number of stops necessary
    FileReader();
    ///calls the other functions
    void load();
    ///distance between two points in meters
    double applyHaversine(double lat1, double lon1, double lat2, double lon2);

    Graph* getGraph(){return graph;}
};


#endif //BUS_SYSTEM_FILEREADER_H
