//
// Created by duart on 24/01/2022.
//

#include <algorithm>
#include "App.h"

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void App::run()
{

    double distance;
    while(true) {
        cout << "Please input the number of meters you are willing to walk between stops if necessary ";
        cin >> distance;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        else break;
    }

     cout << "give the coordinates (x y) or name of the starting stop : ";
     string name;
     cin >> name;
    cout << endl;

     if(is_number(name))
     {
         int y;
         int x = stoi(name); cin >> y;
         graph->localByCoordinates(x,y,distance);
     } //in case user puts a coordinate x,y
     else
     {
         graph->localByName(name,distance);
     }

    cout << "give the coordinates (x y) or name of the destination stop : ";
    cin >> name;
    cout << endl;

    if(is_number(name))
    {
        int y;
        int x = stoi(name); cin >> y;
        graph->destByCoordinates(x,y,distance);
    } //in case user puts a coordinate x,y

    else
    {
        graph->destByName(name,distance);
    }


    cout <<
    "|========================================================================|\n"
    "|                                                                        |\n"
    "|     ____________  _________  ___   _  _________  ____  ___ __________  |\n"
    "|    /  _/ __/  _/ /_  __/ _ \/ _ | / |/ / __/ _ \/ __ \/ _ /_  __/ __/  |\n"
    "|   _/ // _/_/ /    / / / , _/ __ |/    _\ \/ ___/ /_/ / , _// / _\ \    |\n"
    "|  /___/___/___/   /_/ /_/|_/_/ |_/_/|_/___/_/   \____/_/|_|/_/ /___/    |\n"
    "|                                                                        |\n"
    "|                                                                        |\n"
    "|========================================================================|\n"
    "|      Shortest rout                   [1]                               |\n"
    "|      Less stops                      [2]                               |\n"
    "|      Less bus changes                [3]                               |\n"
    "|      Cheapest rout                   [4]                               |\n"
    "|      Return                          [0]                               |\n"
    "|========================================================================|\n";

    int choice;
    while(true) {
        cin >> choice;

        cout << "What is your priority for the rout?" << endl;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        else break;
    }

    switch(choice)
    {
        //
    }

}