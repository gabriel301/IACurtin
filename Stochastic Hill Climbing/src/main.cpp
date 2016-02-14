#include <iostream>
#include <list>
#include "grid.h"
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

int main()
{

    Grid mapGrid;
    Stochastic_Climbing agent;
    string filename;
    int op;
    srand ((time(NULL))); /* initialize random seed: */
    cout<<"1 - Load Map\n2 - Stochastic Hill Climbing\n3 - Random Restart Stochastic Hill Climbing\n4 - Build Map\n5 - Performance Test\n6 - Exit\n";
    cout<<"Option: ";
    cin>>op;
    while (op!=6)
    {
        switch(op)
        {
            case 1:
                cin.ignore();
                cout<<"Filename: ";
                getline(cin,filename);
                mapGrid.clearMap();
                mapGrid.loadMap(filename);
                break;
            case 2:
                if(!mapGrid.empty())
                   agent.Search(&mapGrid,500);
                else
                    cout<<"Please load a map before performing this operation\n\n";
                break;
            case 3:
                if(!mapGrid.empty())
                {
                    int rep;
                    cout<<"Number of Restarts: ";
                    cin>>rep;
                    agent.Search(&mapGrid,500,rep);
                }

                else
                    cout<<"Please load a map before performing this operation\n\n";
                break;
            case 4:
                mapGrid.createMap();
                break;
            case 5:
                int rep;
                cout<<"Number of tests: ";
                cin>>rep;
                agent.performanceTest(&mapGrid,rep,500);
                break;
            case 6: return 0;
        }
        cout<<"1 - Load Map\n2 - Stochastic Hill Climbing\n3 - Random Restart Stochastic Hill Climbing\n4 - Build Map\n5 - Performance Test\n6 - Exit\n";
        cout<<"Option: ";
        cin>>op;
    }




}
