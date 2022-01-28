//
// Created by jeffe on 27/01/2022.
//

#include <iostream>
#include "LinesGraph.h"
#include <queue>

using namespace std;

LinesGraph::LinesGraph(int num) : n(num), nodes(num+2){}



void LinesGraph::addEdge(int src, int dest, int byStop, bool isNight, string name1) {
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
    nodes[src].name = name1;
    nodes[src].adj.push_back({dest, {byStop},isNight});
}

list<int> LinesGraph::bfsPath(int src, int dest)
{
    bfs(src);

    list<int> path;
    int node = nodes[dest].pred;
    while(node != src){
        path.push_front(node);
        node = nodes[node].pred;
    }

    for(int i : path)
    {
        cout << nodes[i].dist << " " << nodes[i].name << endl;
    }

    return path;
}


void LinesGraph::bfs(int v) {
    for (int i = 0; i < n; i++){
        nodes[i].visited = false;
        nodes[i].dist = -1;
    }

    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    nodes[v].dist = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        //cout << u << " "; // show node order
        for (const auto& e : nodes[u].adj) {
            if((e.isNight && night) || (!e.isNight && !night)) {
                int w = e.dest;
                if (!nodes[w].visited) {
                    q.push(w);
                    nodes[w].visited = true;
                    nodes[w].dist = nodes[u].dist + 1;
                    nodes[w].pred = u;
                }
            }
        }
    }
}

void LinesGraph::setTime(int choice) {
    if(choice == 1) night = true;
    else night = false;
}
