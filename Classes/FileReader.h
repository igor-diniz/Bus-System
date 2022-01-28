
#ifndef BUS_SYSTEM_FILEREADER_H
#define BUS_SYSTEM_FILEREADER_H

#include "graph.h"

#include <map>

class FileReader {
    static string path;
    Graph* graph;
    unordered_map<string, int>* CodeID; // codigo da parada e seu id
    unordered_map<string, int>* linesID; //
    unordered_map<string, string> codeNameOfLines; // codigo da linha e seu nome

    vector<string> lines;

    void readStops();
    void readStop(const string& line, int id);
    void readLines();
    void readLine(const string &line, int id);
    void readPaths();
    void readPath(const string& line, ifstream &file);
public:
    FileReader();
    void load();

    double applyHaversine(double lat1, double lon1, double lat2, double lon2);

    Graph* getGraph(){return graph;}
};


#endif //BUS_SYSTEM_FILEREADER_H
