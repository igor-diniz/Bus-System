// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>
#include <string>
#include <cmath>
#include <queue>

using namespace std;

#define INF (INT_MAX/2)

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string line, double distance) {
    if (src<0 || src>n-1 || dest<0 || dest>n-1){
        cout << "Can't add the edge." << endl;
        return;
    }
    nodes[src].adj.push_back({dest, distance, line});
    if (!hasDir) nodes[dest].adj.push_back({src, distance});
    //edges.push_back({src, {dest, distance}});
}


pair<double, double> Graph::getCoordinates(int node) {
    return {nodes[node].latitude, nodes[node].longitude};
}

void Graph::setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude) {
    nodes[id].name = name;
    nodes[id].zone = zone;
    nodes[id].latitude = latitude;
    nodes[id].longitude = longitude;
}

void Graph::setCodeIDInfos(unordered_map<string, int> &codeID){
    this->codeID = codeID;

}


// ----------------------------------------------------------
// 1) Algoritmo de Dijkstra e caminhos mais curtos
// ----------------------------------------------------------

// ..............................
// a) Distância entre dois nós
int Graph::dijkstra_distance(int a, int b) {
    dijkstra(a);
    if (nodes[b].dist == INF) return -1;
    return nodes[b].dist;
}

// ..............................
// b) Caminho mais curto entre dois nós
// TODO
list<int> Graph::dijkstra_path(int a, int b) {
    dijkstra(a);
    list<int> path;
    if (nodes[b].dist == INF) return path;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = nodes[v].pred;
        path.push_front(v);
    }
    return path;
}

list<string>Graph::bfsPath()
{
    bfs(src);
    list<string> path;
    if(!nodes[dest].visited) return path;
    path.push_back(nodes[dest].name);
    int v = dest;
    while(v != src)
    {
        v = nodes[v].pred;
        path.push_front(nodes[v].name);
    }
    return path;
}

double Graph::applyHaversine(double lat1, double lon1, double lat2, double lon2){
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000; //retorna em metros
}

void Graph::generatePossibleFeetPaths(double distance)
{
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            auto pair1 = getCoordinates(i);
            auto pair2 = getCoordinates(j);
            double d = applyHaversine(
                    pair1.first, pair1.second,
                    pair2.first, pair2.second);

            if(d <= distance)
                addEdge(i, j, "feet", distance); //como distancia vai ser usada pra calcular o peso, colocar distancia aqui a 0
        }
    }
}

void Graph::dijkstra(int s) {
    MinHeap<int, int> q(n, -1);
    for (int v=1; v<=n; v++) {
        nodes[v].dist = INF;
        q.insert(v, INF); //priority queue
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            int v = e.dest;
            int w = e.weight;
            if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                nodes[v].dist = nodes[u].dist + w;
                q.decreaseKey(v, nodes[v].dist);
                nodes[v].pred = u;
            }
        }
    }
}

void Graph::setCodeNameOfLinesInfos(unordered_map<string, string> &codeNameOfLines) {
    this->codeNameOfLines = codeNameOfLines;
}

void Graph::bfs(int v) {
// initialize all nodes as unvisited
    for (int v=1; v<=n; v++) nodes[v]. visited = false;
    queue <int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].pred = v;
    nodes[v].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front(); q.pop(); // remove first element of q
      //  cout << u << " "; // show node order
        for (auto e : nodes[u]. adj) {
            int w = e.dest;
            if (! nodes[w]. visited) { // new node!
                q.push(w);
                nodes[w]. visited = true ;
                nodes[w].pred = u;
            }
        }
    }
}


void Graph::localByCoordinates(int x,int y,double distance) {

    setNodeInfo(n-1,"initial","",x,y);
    generatePossibleFeetPaths(distance);
}

void Graph::localByName(string name, double distance)
{
    if(codeID.find(name) == codeID.end()) cerr << "name of the stop is invalid!" << endl;
    src = codeID[name];
    //nodes[n-1] = nodes[codeID[name]];
    //setNodeInfo(n-1,"initial","",nodes[codeID.at(name)].latitude,nodes[codeID.at(name)].longitude);
    generatePossibleFeetPaths(distance);
}

void Graph::destByCoordinates(int x,int y,double distance) {

    setNodeInfo(n,"destination","",x,y);
    generatePossibleFeetPaths(distance);
}

void Graph::destByName(string name, double distance)
{
    if(codeID.find(name) == codeID.end()) cerr << "name of the stop is invalid!" << endl;
    dest = codeID[name];
    //nodes[n] = nodes[codeID[name]];
    //setNodeInfo(n,"destination","",nodes[codeID.at(name)].latitude,nodes[codeID.at(name)].longitude);
    //generatePossibleFeetPaths(distance);
}

void Graph::lessStops()
{
   // return bfsPath();
}

void readFile(string fileName)
{
}

