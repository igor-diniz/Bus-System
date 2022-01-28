//
// Created by jeffe on 27/01/2022.
//

#ifndef BUS_SYSTEM_LINESGRAPH_H
#define BUS_SYSTEM_LINESGRAPH_H
#include <set>
#include <list>
#include <vector>
using namespace std;


class LinesGraph {

    struct Edge{
        int dest; // Destination Line ID
        set<int> stop;
    };

    struct Node{
        list<Edge> adj; // Connections with others lines
        int distance;
        int pred;
        bool visited;
    };

    int n;
    vector<Node> nodes;

public:
    LinesGraph() = default;
    LinesGraph(int num);

    void addEdge(int src, int dest, int byStop);

};


#endif //BUS_SYSTEM_LINESGRAPH_H
