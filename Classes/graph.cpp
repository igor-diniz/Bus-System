// AED 2021/2022 - Aula Pratica 11
// Pedro Ribeiro (DCC/FCUP) [17/01/2022]

#include "graph.h"
#include <climits>
#include <string>
#include <cmath>
#include <queue>
#include <set>
using namespace std;

#define INF (INT_MAX/2)

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num, bool dir) : n(num), hasDir(dir), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, string line, double distance, bool isNight) {
    if (src<0 || src>n-1 || dest<0 || dest>n-1){
        cout << "Can't add the edge." << endl;
        return;
    }
    nodes[src].adj.push_back({dest, distance, line,isNight});
    if (!hasDir) nodes[dest].adj.push_back({src, distance});
    //edges.push_back({src, {dest, distance}});
}


pair<double, double> Graph::getCoordinates(int node) {
    return {nodes[node].latitude, nodes[node].longitude};
}

void Graph::setNodeInfo(int id, const string &name, const string &zone, double latitude, double longitude, string code) {
    nodes[id].name = name;
    nodes[id].zone = zone;
    nodes[id].latitude = latitude;
    nodes[id].longitude = longitude;
    nodes[id].code = code;
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

double Graph::primForPRT1(int r) {
    MinHeap<int, double> heap(n, -1);
    for(int i = 0; i < n; i++){
        nodes[i].dist = INF;
        nodes[i].pred = -1;
        heap.insert(i, nodes[i].dist);
    }
    nodes[r].dist = 0;
    heap.decreaseKey(r,0);

    while(heap.getSize() > 0){
        int smallest = heap.removeMin();
       // cout << nodes[smallest].zone << endl;
        if(nodes[smallest].zone != "PRT1") continue;
        for(auto &edge : nodes[smallest].adj){
            if(heap.hasKey(edge.dest)
               && edge.weight < nodes[edge.dest].dist){
                nodes[edge.dest].pred = smallest;
                nodes[edge.dest].dist = edge.weight;
                heap.decreaseKey(edge.dest, edge.weight);
            }
        }
    }

    double result = 0;
    for(const auto &node : nodes){
        if(node.pred != -1)
            result += node.dist;
    }
    return result;
}

void Graph::removeStop(string name)
{
    nodes[codeID[name]].removed = true;
    nodes[codeID[name]].adj.clear();
    nodes[codeID[name]].longitude = 0;
    nodes[codeID[name]].latitude = 0;
    nodes[codeID[name]].zone = "";
    nodes[codeID[name]].name = "REMOVED";
}


list<int> Graph::bfsPath()
{
    bfs(src);
    list<int> path;
    if(!nodes[dest].visited) return path;
    path.push_back(dest);
   // cout << nodes[src].latitude << " " << nodes[src].longitude << endl;
    int v = dest;
    while(v != src)
    {
        //cout << nodes[v].latitude << " " << nodes[v].longitude << endl;
        cout << nodes[v].name <<  " " << nodes[v].dist << endl;
        v = nodes[v].pred;
        path.push_front(v);
    }

    for(int i : path)
    {
        cout << nodes[i].code << " " << nodes[i].name << endl;
    }

    return path;
}

list<int> Graph::lessDistance()
{
    dijkstra(src);
    list<int> path;
    cout << nodes[dest].dist << endl;
    if (nodes[dest].dist == INF) return path;
    path.push_back(dest);
    int v = dest;
    while (v != src) {
        v = nodes[v].pred;
        cout << nodes[v].dist << " " << nodes[v].name << endl;
        path.push_front(v);
    }

    for(int i : path)
    {
        cout << nodes[i].code << " " << nodes[i].name << endl;
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
                addEdge(i, j, "feet", d,night);
        }
    }
}

void Graph::addCoordinatesEdge(int v, double distance)
{
    auto pair1 = getCoordinates(v);
    for(int i = 0; i < n -1; i++)
    {
        auto pair2 = getCoordinates(i);
        double d = applyHaversine(
                pair1.first, pair1.second,
                pair2.first, pair2.second);
        if(d <= distance && v != i)
        {
            addEdge(i, v, "feet", d,night);
            addEdge(v, i, "feet", d,night);
        }
    }
}


void Graph::dijkstra(int s) {
    MinHeap<int, double> q(n, -1);
    for (int v=0; v<n; v++) {
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
        for (auto &e : nodes[u].adj) {
            if((night && e.isNight) || (!night && !e.isNight)) {
                int v = e.dest;
                double w = e.weight;
                if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                    nodes[v].dist = nodes[u].dist + w;
                    q.decreaseKey(v, nodes[v].dist);
                    nodes[v].pred = u;
                }
            }
        }
    }
}

list<int>Graph::lessZonesPath()
{
    lessZones(src);
    list<int> path;
    if(!nodes[dest].visited) return path;
    path.push_back(dest);
    // cout << nodes[src].latitude << " " << nodes[src].longitude << endl;
    cout << nodes[dest].dist - 1 << " zone(s) passed" << endl;
    int v = dest;
    while(v != src)
    {
       //cout << nodes[v].latitude << " " << nodes[v].longitude << endl;
       // cout << nodes[v].name << endl << nodes[v].zone << endl;
       cout << nodes[v].dist << " " << nodes[v].pred << " " << nodes[v].name << endl;
        v = nodes[v].pred;
        path.push_front(v);
    }

    for(int i : path)
    {
        cout << nodes[i].code << " " << nodes[i].name << endl;
    }
    return path;
}

list<int>Graph::lessLinesPath()
{
    lessLines(src);
    list<int> path;
    if(!nodes[dest].visited) return path;
    path.push_back(dest);
    // cout << nodes[src].latitude << " " << nodes[src].longitude << endl;
    cout << nodes[dest].dist - 1 << " line(s) passed" << endl;
    int v = dest;
    while(v != src)
    {
        //cout << nodes[v].latitude << " " << nodes[v].longitude << endl;
        // cout << nodes[v].name << endl << nodes[v].zone << endl;
        cout << nodes[v].dist << " " << nodes[v].pred << " " << nodes[v].name  << " " << nodes[v].lineUsed << endl;
        v = nodes[v].pred;
        path.push_front(v);
    }

    for(int i : path)
    {
        cout << nodes[i].code << " " << nodes[i].name << endl;
    }
    return path;
}

void Graph::lessLines(int s) // fazer
{
    MinHeap<int, double> q(n, -1);
    for (int v=0; v<n; v++) {
        nodes[v].dist = INF;
        q.insert(v, nodes[v].dist); //priority queue
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    int counter = 0;
    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        for (auto e : nodes[u].adj) {
            if((night && e.isNight) || (!night && !e.isNight)) {
                int v = e.dest;
                if (e.line == "feet" && counter != 0 && nodes[v].name != "destination")
                    e.weight = INF;
                else if(e.line != nodes[u].lineUsed)
                    e.weight = 1;
                else e.weight = 0;

                double w = e.weight;
                if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                    nodes[v].dist = nodes[u].dist + w;
                    q.decreaseKey(v, nodes[v].dist);
                    nodes[v].pred = u;
                    nodes[v].lineUsed = e.line;
                }
            }
        }
        counter = 1;
    }
}

void Graph::lessZones(int s)
{
    MinHeap<int, double> q(n, -1);
    for (int v=0; v<n; v++) {
        nodes[v].dist = INF;
        q.insert(v, nodes[v].dist); //priority queue
        nodes[v].visited = false;
    }
    nodes[s].dist = 0;
    q.decreaseKey(s, 0);
    nodes[s].pred = s;
    string lastZone;
    while (q.getSize()>0) {
        int u = q.removeMin();
        // cout << "Node " << u << " with dist = " << nodes[u].dist << endl;
        nodes[u].visited = true;
        if(nodes[u].zone != " ") lastZone = nodes[u].zone;
        for (auto e : nodes[u].adj) {
            if((night && e.isNight) || (!night && !e.isNight)) {
                int v = e.dest;
                if (nodes[v].zone == lastZone)
                    e.weight = 0;

                else
                    e.weight = 1;

                double w = e.weight;
                if (!nodes[v].visited && nodes[u].dist + w < nodes[v].dist) {
                    nodes[v].dist = nodes[u].dist + w;
                    q.decreaseKey(v, nodes[v].dist);
                    nodes[v].pred = u;
                }
            }
        }
    }
}

void Graph::setCodeNameOfLinesInfos(unordered_map<string, string> &codeNameOfLines) {
    this->codeNameOfLines = codeNameOfLines;
}

void Graph::bfs(int v) {
// initialize all nodes as unvisited
    for (int i=0; i<n; i++) nodes[i].visited = false;
    queue <int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].pred = v;
    nodes[v].visited = true ;
    while (!q.empty ()) { // while there are still unprocessed nodes
        int u = q.front(); q.pop(); // remove first element of q
      //  cout << u << " "; // show node order
        for (auto &e : nodes[u].adj) {
            if((night && e.isNight) || (!night && !e.isNight)) {
                int w = e.dest;
                if (!nodes[w].visited && !nodes[w].removed) { // new node!
                    q.push(w);
                    nodes[w].visited = true;
                    nodes[w].pred = u;
                }
            }
        }
    }
}


void Graph::localByCoordinates(double x, double y, double distance) {

    src = n - 2;
    setNodeInfo(src,"initial"," ",x,y,"INIT");
    addCoordinatesEdge(src,distance);
    /*for(auto a: nodes[src].adj)
    {
        cout << a.dest << " " << a.line << nodes[a.dest].name << endl;
    }*/
    generatePossibleFeetPaths(distance);
}

void Graph::localByName(string name, double distance)
{
    if(codeID.find(name) == codeID.end()) cerr << "name of the stop is invalid!" << endl;
    src = n - 2;
    cout << nodes[codeID[name]].name << " " << nodes[codeID[name]].latitude << " " << nodes[codeID[name]].longitude << endl;
    setNodeInfo(src,"origin","",nodes[codeID[name]].latitude,nodes[codeID[name]].longitude,"ORIG");
    addCoordinatesEdge(src,distance);
    //nodes[n-1] = nodes[codeID[name]];
    //setNodeInfo(n-1,"initial","",nodes[codeID.at(name)].latitude,nodes[codeID.at(name)].longitude);
    generatePossibleFeetPaths(distance);
}

void Graph::destByCoordinates(double x, double y, double distance) {

    dest = n - 1;
    setNodeInfo(dest,"destination"," ",x,y,"DEST");
    addCoordinatesEdge(dest,distance);
    /*for(auto a: nodes[dest].adj)
    {
        cout << a.dest << " " << a.line << nodes[a.dest].name << endl;
    }*/
    // generatePossibleFeetPaths(distance);
}

void Graph::destByName(string &name, double distance)
{
    if(codeID.find(name) == codeID.end()) cerr << "name of the stop is invalid!" << endl;
    dest = n - 1;
    setNodeInfo(dest,"destination","",nodes[codeID[name]].latitude,nodes[codeID[name]].longitude,"DEST");
    //nodes[n] = nodes[codeID[name]];
    //setNodeInfo(n,"destination","",nodes[codeID.at(name)].latitude,nodes[codeID.at(name)].longitude);
    //generatePossibleFeetPaths(distance);
    addCoordinatesEdge(dest,distance);

}

void Graph::setTime(int choice) {
    if(choice == 1) night = true;
    else night = false;
}

list<Graph::Edge> Graph::getEdges(int node) {
    return nodes[node].adj;
}


