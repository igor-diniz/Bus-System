
#include <FileReader.h>

using namespace std;

int main(void) {
    FileReader f;
    Graph* g = f.load();
    list<string> a;
    g->localByName("ERM3",30);
    g->destByName("PTCR2",30);
    a = g->bfsPath();
    for(auto i: a)
    {
        cout << i << endl;
    }
    return(0);
}