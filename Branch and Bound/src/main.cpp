#include <iostream>
#include <fstream>
#include "t_graph.h"
#include "branch.h"
#include <sstream> //istringstream
using namespace std;

int main()
{
    t_graph Graph;
    Branch_and_Bound search;
    int op,ptrposition;
    char v1,v2;
    double w;
    ifstream file;
    istringstream stream;
    string src,aux,line;
    cout<<"1 - Load Graph\n2 - Branch and Bound Search\n3 - Quit\n";
    cout<<"\nOption: ";
    cin>> op;

    while(op!=3)
    {
        if(op==1)
        {
            Graph.clear();
            cout<<"Graph Source file Destination: ";
            cin.ignore();
            getline(cin,src);
            file.open(src.c_str());

            if(!file)
            {
                cout<<"Error while opening the file.\n";
                return 0;
            }


            while(!file.eof())
            {
                getline(file,line);
                //Avoid reading blank lines
                if(!line.empty())
                {
                    stream.clear();
                    stream.str(line);
                    stream>>v1>>v2>>w;
                    Graph.addUndirectedEgde(v1,v2,w);
                }

            }
            file.close();

        }
        else if(op==2)
        {
            if(!Graph.empty())
            {
                cin.ignore();
                cout<<"Source and Goal Vertex: ";
                cin>>v1>>v2;
                search.Search(&Graph,v1,v2);
            }
            else
            {
                cout<<"Graph is empty. Please load a graph before performing this operation\n";
            }

        }
        else if (op==3)
        {
            return 0;
        }

        cout<<"1 - Load Graph\n2 - Branch and Bound Search\n3 - Quit\n";
        cout<<"\nOption: ";
        cin>> op;
    }
}
