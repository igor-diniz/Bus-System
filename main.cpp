
#include <FileReader.h>

using namespace std;

int main(void) {
    FileReader f;
    Graph* g = f.load();
    list<string> a;
    g->localByCoordinates(41.2166 ,-8.5536,30);
    g->destByCoordinates(41.2111, -8.55729,30);
   // g->localByName("ERM3",30);
   // g->destByName("PTCR2",30);
    a = g->bfsPath();
    for(auto i: a)
    {
        cout << i << endl;
    }
    return(0);
}