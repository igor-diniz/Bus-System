// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "minHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <map>

using namespace std;

class Graph {
    struct Edge { //os edges vão ser criados dos ficheiros LINE_CODE_DIR.CSV,
                    //sendo line = CODE
                    //
        int dest;   // Destination node, read from LINE_CODE_DIR.CSV
        double weight; // An integer weight, default value, talvez distãncia entre eles?
        string line; // line cod from lines.csv
        string name; // name from lines.csv
        bool isNight; // se a linha é noturna
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int dist; //starts on -1
        int pred; //starts on -1
        bool visited; //starts on false
        string name; //name of stops.csv
        string code; //code of stops.csv
        string zone; //zone of stops.csv
        int latitude; //latitude of stops.csv
        int longitude; //longitude of stops.csv
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    bool hasDir;        // false: undirect; true: directed
    vector<Node> nodes; // The list of nodes being represented
    map<string,int> codes; // pra cada codigo que formos adicionar, ser representado por um inteiro ex, codes["1AL2"] = 1

    void dijkstra(int s);

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes, bool dir = false);

    // Add edge from source to destination with a certain weight
    void setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude);
    void addEdge(int src, int dest, const string &line = "", double weight = 0);

    pair<double,double> getCoordinates(int node);

    typedef pair<int,pair<int,double>> edgeInfo;
    vector<edgeInfo> edges; // {source, {destiny, weight} }

    // ----- Functions to implement in this class -----
    int dijkstra_distance(int a, int b);
    list<int> dijkstra_path(int a, int b);
};

#endif
