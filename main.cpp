
#include <FileReader.h>
#include <App.h>

using namespace std;

int main(void) {

    App app;

    app.run();

    /*FileReader f;
    Graph* g = f.load();
    list<string> a;
    g->localByCoordinates(41.2166 ,-8.5536,200);
    g->destByCoordinates(41.14954216,-8.610023615,200);
    g->localByName("ERM3",200);
    g->destByName("1AL2",200);
    a = g->lessZonesPath(); // menos zonas
    a = g->lessStopsPath(); // menos paragens
    a = g->lessDistancePath(); // menor distancia

    for(auto i: a)
    {
        cout << i << endl;
    }
    return(0);
    // "PINC2"
    // 31JA3,31 DE JANEIRO,MTS2,41.22589684,-8.684105266
    // 1AL2,AV.ALIADOS,PRT1,41.14954216,-8.610023615*/
}