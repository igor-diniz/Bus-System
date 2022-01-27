// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <map>
#include <set>

using namespace std;

class Graph {
    struct Edge { //os edges vão ser criados dos ficheiros LINE_CODE_DIR.CSV,
                    //sendo line = CODE
                    //
        int dest;   // Destination node, read from LINE_CODE_DIR.CSV
        double weight; // An integer weight, default value, talvez distãncia entre eles?
        string line; // line cod from lines.csv
        bool isNight; // se a linha é noturna
        //string name; // name from lines.csv
    };

    struct Node {

        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited; //starts on false
        string name; //name of stops.csv
        string zone; //zone of stops.csv
        double latitude; //latitude of stops.csv
        double longitude; //longitude of stops.csv
        double dist; //starts on -1, distancia de um nó a outro (usado no dijkstra)
        int pred; //starts on -1, nó que deu origem (usado no dijkstra)
        //string code; //code of stops.csv
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    unordered_map<string, int> codeID; // codigo da parada e seu id
    unordered_map<string, string> codeNameOfLines; // codigo da linha e seu nome
    int dest,src;
    bool night;

    void dijkstra(int s);
    double applyHaversine(double lat1, double lon1, double lat2, double lon2);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph()= default;
    Graph(int nodes, bool dir = false);
    void setCodeIDInfos(unordered_map<string, int> &codeID);
    void setCodeNameOfLinesInfos( unordered_map<string, string> &codeNameOfLines);

    void setTime(int choice);

    // Add edge from source to destination with a certain weight
    void setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude);
    void addEdge(int src, int dest, string line, double distance, bool isNight = false);
    int size() const {return n;}
    void localByCoordinates(double x, double y, double distance);
    

    pair<double,double> getCoordinates(int node);
    void generatePossibleFeetPaths(double distance);

    // ----- Functions to implement in this class -----
    int dijkstra_distance(int a, int b);
    list<int> dijkstra_path(int a, int b);

    void localByName(string name, double distance);


    void bfs(int v);

    void destByCoordinates(double x, double y, double distance);

    void destByName(string &name, double distance);

    list<string> bfsPath();

    void addCoordinatesEdge(int i, double d);

    void lessZones(int s);

    list<string> lessZonesPath();

    list<string> lessDistance();
};

#endif
