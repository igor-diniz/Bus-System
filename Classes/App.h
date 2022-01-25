//
// Created by duart on 24/01/2022.
//

#ifndef BUS_SYSTEM_APP_H
#define BUS_SYSTEM_APP_H

#include "graph.h"
#include "FileReader.h"

class App
{
    Graph* graph;
    FileReader fileReader;
public:
    App() {graph = fileReader.load();};

};

#endif //BUS_SYSTEM_APP_H
