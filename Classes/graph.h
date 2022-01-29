#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

class Graph {
    struct Edge {

        int dest;
        double weight;
        string line;
        bool isNight;
        bool removed = false;
    };

    struct Node {

        list<Edge> adj;
        bool visited;
        string name;
        string zone;
        double latitude;
        double longitude;
        double dist;
        int pred;
        string code;
        string lineUsed;
        bool removed = false;
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string, int> codeID; // codigo da parada e seu id
    int dest,src;
    bool night = false;

    void lessDistance(int source);
    double applyHaversine(double lat1, double lon1, double lat2, double lon2);

public:

    Graph()= default;
    explicit Graph(int nodes, bool dir = false);
    void setCodeIDInfos(unordered_map<string, int> &codeID);
    void changeTime();
    void setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude, string code);
    void addEdge(int source, int destination, string line, double distance, bool isNight = false);
    int size() const {return n;}
    void localByCoordinates(double x, double y, double distance);
    pair<double,double> getCoordinates(int node);
    void generatePossibleFeetPaths(double distance);
    void localByName(string &name, double distance);
    void lessStops(int v);
    void destByCoordinates(double x, double y, double distance);
    void destByName(string &name, double distance);
    void lessStopsPath();
    void addCoordinatesEdge(int i, double d);
    void lessZones(int s);
    void lessLines(int source);
    void lessZonesPath();
    void lessDistancePath();
    void lessLinesPath();
    double primForGDM1();
    void removeStop(string &name);
    void removeLine(unordered_set<string> stringSet);
};

#endif
