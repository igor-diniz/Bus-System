//
// Created by jeffe on 27/01/2022.
//

#ifndef BUS_SYSTEM_LINESGRAPH_H
#define BUS_SYSTEM_LINESGRAPH_H
#include <set>
#include <list>
#include <vector>
#include <unordered_map>
using namespace std;


class LinesGraph {

    struct Edge{
        int dest; // Destination Line ID
        set<int> stop;
        bool isNight;
    };

    struct Node{
        list<Edge> adj; // Connections with others lines
        int dist = -1;
        int pred = -1;
        bool visited = false;
        string name;
    };

    int n;
    vector<Node> nodes;
    bool night;
    unordered_map<string, int>* linesID;

public:
    LinesGraph() = default;
    explicit LinesGraph(int num);

    void setLinesID(unordered_map<string, int>*& linesIDs) {this->linesID = linesIDs;}

    void addEdge(int src, int dest, int byStop, bool isNight, string name1);

    void setTime(int choice);

    void bfs(int v);

    list<int> bfsPath(int src, int dest);
};


#endif //BUS_SYSTEM_LINESGRAPH_H
