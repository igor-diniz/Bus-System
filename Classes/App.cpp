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

    //cout << graph->primForPRT1(1) << endl;

    cout << "Do you want to remove any stops? if yes, write their code (ex: ERM3) separated by a space and type 0 to continue" << endl;
    string removed;

    while(cin >> removed)
    {
        if(removed == "0") break;
        graph->removeStop(removed);
    }

    double distance;
    while(true) {
        cout << "Please input the number of meters you are willing to walk between stops if necessary \n";
        cin >> distance;

        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }
        else break;
    }

    int choice;
    while (true) {
        cout << "Do you want day (0) or night (1) paths? \n";
        cin >> choice;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Invalid input!" << endl;
            continue;
        } else break;
    }

    graph->setTime(choice);

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


    while(true) {
        cout <<
             "|========================================================================|\n"
             "|                                                                        |\n"
             "|     ____________  _________  ___   _  _________  ____  ___ __________  |\n"
             "|    /  _/ __/  _/ /_  __/ _ \\/ _ | / |/ / __/ _ \\/ __ \\/ _ /_  __/ __/  |\n"
             "|   _/ // _/_/ /    / / / , _/ __ |/    _\\ \\/ ___/ /_/ / , _// / _\\ \\    |\n"
             "|  /___/___/___/   /_/ /_/|_/_/ |_/_/|_/___/_/   \\____/_/|_|/_/ /___/    |\n"
             "|                                                                        |\n"
             "|                                                                        |\n"
             "|========================================================================|\n"
             "|      Shortest rout                   [1]                               |\n"
             "|      Less stops                      [2]                               |\n"
             "|      Less bus changes                [3]                               |\n"
             "|      Cheapest rout                   [4]                               |\n"
             "|      Exit                            [0]                               |\n"
             "|========================================================================|\n";

        while (true) {
            cout << "What is your priority for the rout?" << endl;
            cin >> choice;

            if (cin.fail() || cin.peek() != '\n') {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input!" << endl;
                continue;
            } else break;
        }

        list<int> names;

        switch (choice) {
            case 0:
                exit(0);
            case 1:
                graph->lessDistance();
                break;
            case 2:
                graph->bfsPath();
                break;
            case 3:
                graph->lessLinesPath();
                break;
            case 4:
                graph->lessZonesPath();
                break;
            default:
                cout << "invalid choice!" << endl;
        }
    }
}