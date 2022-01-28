#include "FileReader.h"
#include "LinesGraph.h"

#include <dirent.h>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;
int calculateNumberOfStops(){
    std::ifstream inFile("../dataset/stops.csv");
    return std::count(std::istreambuf_iterator<char>(inFile),
                      std::istreambuf_iterator<char>(), '\n') - 1;
}

int calculateNumberOfLines(){
    std::ifstream inFile("../dataset/lines.csv");
    return (int)std::count(std::istreambuf_iterator<char>(inFile),
                           std::istreambuf_iterator<char>(), '\n') - 1;
}

FileReader::FileReader() {
    int numberStops = calculateNumberOfStops();
    cout << "Number of stops detected: " << numberStops << endl;

    graph = new Graph(calculateNumberOfStops() + 2, true); // 2 a mais pq esses espaços vao ser usados para os calculos
    linesGraph = new LinesGraph(calculateNumberOfLines());
    CodeID = new unordered_map<string, int>(numberStops);
    linesID = new unordered_map<string, int>(calculateNumberOfLines());
}

string FileReader::path = "../dataset/";

void FileReader::readStops() {
    ifstream readingStops;
    ifstream file(path + "stops.csv");
    if(!file.is_open()) cerr << "File not found" << endl;
    else cout << "File opened" << endl;

    string fileContent;

    getline(file, fileContent);// primeira linha ignorada

    int stopID = 0;
    while(getline(file, fileContent)){
        //cout << fileContent << endl;
        readStop(fileContent, stopID++);
    }
    graph->setNodeInfo(graph->size()-2,"origin","0",0,0,"ORIG");
    graph->setNodeInfo(graph->size()-1,"destination","0",0,0,"DEST");
}

void FileReader::readStop(const string &line, int id){
    istringstream reader(line);
    string code, name, zone;
    double latitude, longitude;
    char separator;

    getline(reader, code, ',');
    getline(reader, name, ',');
    getline(reader, zone, ',');
    reader >> latitude >> separator >> longitude;

    graph->setNodeInfo(id, name, zone, latitude, longitude,code);
    CodeID->insert({code, id}); // os códigos do ficheiro stops.csv são mapeados para um id
}

void FileReader::readLines() {
    ifstream file(path + "lines.csv");
    if(!file.is_open()) cerr << "File not found" << endl;
    else cout << "File opened" << endl;

    string fileContent;

    getline(file, fileContent); //primeira linha ignorada

    int lineID = 0;

    while(getline(file, fileContent)){
        //cout << fileContent << endl;
        readLine(fileContent, lineID++);
    }
}

void FileReader::readLine(const string &line, int id) {
    istringstream reader(line);
    string code, name;

    getline(reader, code, ',');
    getline(reader, name);

    codeNameOfLines.insert({code, name});
    lines.push_back(code);
    linesID->insert({code, id});
}

double FileReader::applyHaversine(double lat1, double lon1, double lat2, double lon2){
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}

void FileReader::readPaths() {
    for(auto & it : codeNameOfLines){
        ifstream file0(path + "line_" + it.first + "_0.csv");
        ifstream file1(path + "line_" + it.first + "_1.csv");

        if(file0.is_open())
            readPath(it.first, file0);
        else cerr << "File cannot be opened!" << endl;

        if(file1.is_open())
            readPath(it.first, file1);
        else cerr << "File cannot be opened!" << endl;
    }
}

void FileReader::readPath(const string& line, ifstream &file) {
    int num; file >> num;
    string source; file >> source;
    bool isNight = false;
    if(line.back() == 'M')
    {
        isNight = true;
    }

    for(int i = 0; i < num - 1; i++){
        string dest; file >> dest;
        int sourceID = CodeID->at(source);
        int destID = CodeID->at(dest);

        auto pair1 = graph->getCoordinates(sourceID);
        auto pair2 = graph->getCoordinates(destID);

        graph->addEdge(sourceID, destID, line,
                applyHaversine(
                        pair1.first, pair1.second,
                        pair2.first, pair2.second
                ),
                isNight);

        source = dest;
    }
}

void FileReader::load() {
    readStops();
    readLines();
    readPaths();
    loadLinesGraph();
    //calculatePossibleFeetPaths(0); // isso ainda vai ser pedido pro usuario, tlvz dps mande isso pro graph
    linesGraph->setLinesID(linesID);
    graph->setCodeIDInfos(*CodeID);
    graph->setCodeNameOfLinesInfos(codeNameOfLines);
}

void FileReader::loadLinesGraph() {
    //for(auto i = graph->getEdges(graph->size()).begin(); i != graph->getEdges(graph->size()).end(); i++)
    //cout<< (*i).line << " " << i->dest << endl;
    for(int i = 0; i < graph->size(); i++){
        for(const auto& e1 : graph->getEdges(i)){
            for(const auto& e2 : graph->getEdges(e1.dest)){
                if(e1.line == e2.line) continue;
                if(e1.line == "feet" || e2.line == "feet") continue;
                if(e1.line == "11M" && e2.line == "901") {
                    //cout << e1.dest << endl;
                }
                linesGraph->addEdge(linesID->at(e1.line), linesID->at(e2.line), e1.dest,e1.isNight, e1.line);
                //linesConnections.insert({{e1.line, e2.line}, e1.dest});
            }
        }
    }

   /* for(const auto& c : linesConnections)
        linesGraph->addEdge(linesID->at(c.first.first), linesID->at(c.first.second), c.second); */
}

/*void FileReader::calculatePossibleFeetPaths(double distance) {
    for(int i = 0; i < graph->size() - 1; i++){
        for(int j = i + 1; j < graph->size(); j++){
            auto pair1 = graph->getCoordinates(i);
            auto pair2 = graph->getCoordinates(j);
            double d = applyHaversine(
                    pair1.first, pair1.second,
                    pair2.first, pair2.second);

            if(d <= distance)
                graph->addEdge(i, j, "feet", distance);
        }
    }
}*/


