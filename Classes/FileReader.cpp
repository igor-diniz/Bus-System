#include "FileReader.h"

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

FileReader::FileReader() {
    int numberStops = calculateNumberOfStops();

    graph = new Graph(calculateNumberOfStops() + 2, true); // 2 a mais pq esses espaços vao ser usados para os calculos
    codeID = new unordered_map<string, int>(numberStops);
}

string FileReader::path = "../dataset/";

void FileReader::readStops() {
    ifstream readingStops;
    ifstream file(path + "stops.csv");
    if(!file.is_open()) cerr << "File not found" << endl;

    string fileContent;

    getline(file, fileContent);// primeira linha ignorada

    int stopID = 0;
    while(getline(file, fileContent)){
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
    codeID->insert({code, id}); // os códigos do ficheiro stops.csv são mapeados para um id
}

void FileReader::readLines() {
    ifstream file(path + "lines.csv");
    if(!file.is_open()) cerr << "File not found" << endl;

    string fileContent;

    getline(file, fileContent); //primeira linha ignorada

    while(getline(file, fileContent)){
        readLine(fileContent);
    }
}

void FileReader::readLine(const string &line) {
    istringstream reader(line);
    string code, name;

    getline(reader, code, ',');
    getline(reader, name);

    codeNameOfLines.insert({code, name});
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
        int sourceID = codeID->at(source);
        int destID = codeID->at(dest);

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
    graph->setCodeIDInfos(*codeID);
}



