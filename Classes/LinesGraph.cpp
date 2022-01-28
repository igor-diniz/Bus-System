//
// Created by jeffe on 27/01/2022.
//

#include <iostream>
#include "LinesGraph.h"

using namespace std;

LinesGraph::LinesGraph(int num) {
    n = num;
    nodes = vector<Node>(num + 2);
}

void LinesGraph::addEdge(int src, int dest, int byStop) {
    if(src < 0 || src > n + 1 || dest < 0 || dest > n + 1){
        cout << "Can't add the edge." << endl;
        return;
    }

    /*if(src == 13 && dest == 6)
        cout << "";*/
    for(auto& e : nodes[src].adj){
        if(e.dest == dest){
            e.stop.insert(byStop);
            return;
        }
    }
    nodes[src].adj.push_back({dest, {byStop}});
}
