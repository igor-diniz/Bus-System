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
    FileReader fileReader = FileReader();
public:
    App() {fileReader.load(); graph = fileReader.getGraph(); run();};
    void run();

    void removeStop();

    void removeLine();
};

#endif //BUS_SYSTEM_APP_H
