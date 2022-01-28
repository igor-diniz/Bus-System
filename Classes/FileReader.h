
#ifndef BUS_SYSTEM_FILEREADER_H
#define BUS_SYSTEM_FILEREADER_H

#include "graph.h"
#include "LinesGraph.h"
#include <map>

class FileReader {
    static string path;
    Graph* graph;
    LinesGraph *linesGraph;
    unordered_map<string, int>* CodeID; // codigo da parada e seu id
    unordered_map<string, int>* linesID; //
    unordered_map<string, string> codeNameOfLines; // codigo da linha e seu nome

    vector<string> lines;
    multimap<pair<string,string>,int> linesConnections;

    void readStops();
    void readStop(const string& line, int id);
    void readLines();
    void readLine(const string &line, int id);
    void readPaths();
    void readPath(const string& line, ifstream &file);
    //void calculatePossibleFeetPaths(double distance);
public:
    FileReader();
    Graph* load();

    double applyHaversine(double lat1, double lon1, double lat2, double lon2);

    void loadLinesGraph();

    Graph* getGraph(){return graph;}

    LinesGraph* getLinesGraph() {return linesGraph;}
};


#endif //BUS_SYSTEM_FILEREADER_H
