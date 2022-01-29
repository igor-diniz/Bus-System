#ifndef BUS_SYSTEM_APP_H
#define BUS_SYSTEM_APP_H

#include "graph.h"
#include "FileReader.h"

class App
{
    Graph* graph;
    FileReader fileReader = FileReader();
public:

    ///makes the fileReader load the graphs, and put the loaded graph into the variable graph
    ///call run() after that
    App() {fileReader.load(); graph = fileReader.getGraph(); run();};
    /// runs the interface to user
    void run();
    /// used to call the remove stop from the graph with the necessary arguments
    void removeStop();
    /// used to call the remove line from the graph with the necessary arguments
    void removeLine();
};

#endif //BUS_SYSTEM_APP_H
