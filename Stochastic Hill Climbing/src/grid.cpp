#include "grid.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cmath>
#include <sstream>    //istringstream

using namespace std;

//******Grid Class Methods*********//
 void Grid::clearMap()
 {
     space.clear();
     z=0;
 }


//This function re-map the coordinates of any map to coordinates in origin (beginning in point (0,0)
 void Grid::loadMap(string filename)
 {
     ifstream file;
     double a,b,c, current;
     string line;
     int x,y;
     istringstream stream;
     bool first; //Flag to set first iteration
     file.open(filename.c_str());
     if(!file)
     {
         cout<<"Error while opening the file.\n";
         return;
     }


    x=-1;
    y=-1;
    first = true;
    current = -1;
        while(!file.eof())
        {

            getline(file,line);
            //Avoid reading blank lines
            if(!line.empty())
            {
                stream.clear();
                stream.str(line);
                stream>>a>>b>>c;
                if(current!=a || first)
                {
                    y=-1;
                    x++;
                    current = a;
                    first = false;
                }
                //Got the highest value of z
                y++;
                if(c>this->z) this->z = c;
                space[make_pair(x,y)] = new Point(a,b,c);


            }

        }

    pts = make_pair(x+1,y+1);
    file.close();
 }

//Print the map loaded in a file
void Grid::printFile()
{
    ofstream file;
    map<pair<int,int>,Point*>::iterator it;

    file.open("map-printed.txt");
    if(!file)
    {
         cout<<"Error while opening the file.\n";
         return;
    }
    for(it=space.begin(); it != space.end();it++)
    {
        file<<it->second->x<<" "<<it->second->y<<" "<<it->second->z<<"\n";
    }
}


//Return the dimensions of the load map
pair<int,int> Grid::getDimensions()
{
    return pts;
}


//Return whether a map is load in memory
bool Grid::empty()
{
    return space.empty();
}

//Create a file  containing a map with shoulders
void Grid::createShoulderMap()
{
    int x,y,z;
    ofstream file;
     file.open("shoulders.txt");
    for(x=0;x<900;x+=10)
    {
        z=0;
        for(y=0;y<100;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }
        z+=500;
        for(y=100;y<200;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
            z+=500;
        }
        for(y=200;y<300;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }
        z+=1000;
        for(y=300;y<400;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
            z+=1000;
        }
        for(y=400;y<500;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

        z-=1000;
        for(y=500;y<600;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
            z-=1000;
        }

        for(y=600;y<700;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";

        }
        z-=500;
        for(y=700;y<800;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
            z-=500;
        }
        for(y=800;y<900;y+=10)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";

        }
    }
    file.close();
    cout<<"File shoulders.txt is created\n";
}


//Create a file  containing a map with random points
void Grid::createRandomMap()
{
    int x,y,z;
    ofstream file;
     file.open("random.txt");
    for(x=0;x<900;x+=10)
    {

        for(y=0;y<100;y+=10)
        {
            z = rand() % 10;
            file<<x<<" "<<y<<" "<<z<<"\n";
        }
        for(y=100;y<200;y+=10)
        {
            z = rand() % 100 + 10;
            file<<x<<" "<<y<<" "<<z<<"\n";
        }
        for(y=200;y<300;y+=10)
        {
            z = rand() % 500 + 110;
            file<<x<<" "<<y<<" "<<z<<"\n";
        }
        for(y=300;y<400;y+=10)
        {
            z = rand() % 1000 + 610;
            file<<x<<" "<<y<<" "<<z<<"\n";
        }
        for(y=400;y<500;y+=10)
        {
            z = rand() % 1100 + 1610;
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

        for(y=500;y<600;y+=10)
        {
            z = rand() % 1200 + 2710;
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

        for(y=600;y<700;y+=10)
        {
            z = rand() % 1500 + 3810;
            file<<x<<" "<<y<<" "<<z<<"\n";

        }
        for(y=700;y<800;y+=10)
        {
            z = rand() % 1700 + 5310;
            file<<x<<" "<<y<<" "<<z<<"\n";
        }
        for(y=800;y<900;y+=10)
        {
            z = rand() % 2000 + 7010;
            file<<x<<" "<<y<<" "<<z<<"\n";

        }

    }
    file.close();
    cout<<"File random.txt is created\n";
}

//Create a file containing a map with one pick
void Grid::createOnePickMap()
{
    int x,y,w;
    double z;
    ofstream file;
    file.open("onepick.txt");
    for(x=0;x<64;x+=1)
    {
        z=0;
        for(y=0;y<4;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }


     //Parabola: Z = -(w-4)^2 + 64 -4 <= w <= 4
        w = -4;
        for(y=4;y<20;y+=1)
        {
            z = (-1*pow(w-4,2)) + 64;
            file<<x<<" "<<y<<" "<<z<<"\n";
            w++;
        }

        z=0;
        for(y=20;y<24;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }
    }
    file.close();
    cout<<"File onepick.txt is created\n";
}

//Create a file containing a map with multiple local maxima
void Grid::createMultiLocalMaxima()
{
    int x,y,w;
    double z;
    ofstream file;
    file.open("multiplelocal.txt");


    for(x=0;x<64;x+=1)
    {
        z=0;
        for(y=0;y<4;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }


     //Parabola: Z = -(w-4)^2 + 64 -4 <= w <= 4
        w = -4;
        for(y=4;y<20;y+=1)
        {
            z = (-1*pow(w-4,2)) + 64;
            file<<x<<" "<<y<<" "<<z<<"\n";
            w++;
        }

        z=0;
        for(y=20;y<24;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

       //Parabola: Z = -(w-4)^2 + 64 -4 <= w <= 4

        w = -4;
        for(y=24;y<40;y+=1)
        {
            z = (-1*pow(w-4,2)) + 64;
            file<<x<<" "<<y<<" "<<z<<"\n";
            w++;
        }

        z=0;
        for(y=40;y<44;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

        //Parabola: Z = -(w-4)^2 + 64 -4 <= w <= 4
        w = -4;
        for(y=44;y<60;y+=1)
        {
            z = (-1*pow(w-4,2)) + 64;
            file<<x<<" "<<y<<" "<<z<<"\n";
            w++;
        }

        z=0;

        for(y=60;y<64;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

    }

    file.close();
    cout<<"File multiplelocal.txt is created\n";
}

//Create a file containing a map with multiple picks
void Grid::createMultiplePicks()
{
    int x,y,w;
    double z;
    ofstream file;
    file.open("multiplepicks.txt");

    for(x=0;x<64;x+=1)
    {
        z=0;
        for(y=0;y<4;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }


     //Parabola: Z = -(w-4)^2 + 64 -4 <= w <= 4
        w = -4;
        for(y=4;y<20;y+=1)
        {
            z = (-1*pow(w-4,2)) + 64;
            file<<x<<" "<<y<<" "<<z<<"\n";
            w++;
        }

        z=0;
        for(y=20;y<24;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

      //Parabola: Z = -(w-8)^2 + 256 -8 <= w <= 8

        w = -8;
        for(y=24;y<56;y+=1)
        {


            z = (-1*pow(w-8,2)) + 256;
            file<<x<<" "<<y<<" "<<z<<"\n";
            w++;
        }


        z=0;
        for(y=56;y<60;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

        //Parabola: Z = -(w-4)^2 + 64 -4 <= w <= 4
        w = -4;
        for(y=60;y<76;y+=1)
        {

            z = (-1*pow(w-4,2)) + 64;
            file<<x<<" "<<y<<" "<<z<<"\n";
            w++;
        }
        z=0;
        for(y=76;y<80;y+=1)
        {
            file<<x<<" "<<y<<" "<<z<<"\n";
        }

    }

    file.close();
    cout<<"File multiplepicks.txt is created\n";
}

//Create one of maps described above
void Grid::createMap()
{
    int op;
    cout<<"1 - Shoulders Map\n2 - One Pick Map\n3 - Multiple Local Maxima\n4 - Multiple Picks w/ Global Maxima\n5 - Random Points \n";
    cout<<"Option: ";
    cin>>op;
    switch(op)
    {
        case 1:
            createShoulderMap();
        break;
        case 2:
            createOnePickMap();
        break;
        case 3:
            createMultiLocalMaxima();
        break;
        case 4:
            createMultiplePicks();
        break;
         case 5:
            createRandomMap();
        break;
    }
}



/***Stochastic Hill Climbing Methods****/

//Write the sequence of visited points in a file
void Stochastic_Climbing::printFile(Grid *mapGrid)
{
     list<Point *>::iterator it;
     ofstream file;
     file.open("seq.txt");
     for(it=trace.begin();it!=trace.end();it++)
       file<<(*it)->x<<" "<<(*it)->y<<" "<<(*it)->z<<"\n";

     file.close();
}

//clear the list of visited points
void Stochastic_Climbing::clear()
{
    trace.clear();
}

//Generates one neighbor of the current point randomly
pair<int,int> Stochastic_Climbing::getRandomNeighbor(pair<int,int> current, pair<int,int> dimensions)
{
    int num,x,y, xD,yD;
    x=-1;
    y=-1;

    //Get bounds of each axis
    xD = dimensions.first-1;
    yD = dimensions.second-1;

    //While any of axis are out of bound or it is exactly the current node, raffle a number
    while((x>xD|| x<0) || (y>yD|| y<0) || (x==current.first && y==current.second))
    {
        //Generate 1 of 8 possibilities of neighbors (Assuming agent can move diagonally)
        num = rand()%8;

        switch (num)
        {

           //(x-1,y-1)
           case 0:
               x = current.first-1;
               y = current.second-1;
               break;
           //(x-1,y)
           case 1:
               x = current.first-1;
               y = current.second;
               break;
           //(x-1,y+1)
           case 2:
               x = current.first-1;
               y = current.second+1;
               break;
            //(x,y+1)
           case 3:
               x = current.first;
               y = current.second+1;
               break;
            //(x+1,y+1)
           case 4:
               x = current.first+1;
               y = current.second+1;
               break;
            //(x+1,y)
           case 5:
               x = current.first+1;
               y = current.second;
               break;
           //(x+1,y-1)
           case 6:
               x = current.first+1;
               y = current.second-1;
               break;
           //(x,y-1)
           case 7:
               x = current.first;
               y = current.second-1;
               break;
        }

    }

    return make_pair(x,y);

}


/*Search method. Repetition param has a default value 1
(it means it will be performed Stochastic Hill Climbing).
If other value is passed as param, a Random Restart Stochastic Hill Climbing
will be performed (Repetitions = number of restarts of searching)*/
pair<int,int> Stochastic_Climbing::iSearch(Grid *mapSpace,int  numsidesteps, int repetitions)
{
   pair<int,int> dimensions,current,bestSolution,candidate;
   int x,y, steps;
   Point *currSolution = NULL;
   map<pair<int,int>,Point*>::iterator it;

   //Clear information of previous search
   this->clear();

   //Get map dimensions
   dimensions = mapSpace->getDimensions();


   for(int i=0; i<repetitions;i++)
   {
       /* initialize random seed: */
       //srand ((time(NULL)));
       /*Generate a number between 0 and X dimension*/
       x = rand() % dimensions.first;
        /*Generate a number between 0 and Y dimension*/
       y = rand() % dimensions.second;

       //Set the raffled pair as current node
       current.first = x;
       current.second = y;


       //Insert the current node into trace list
       trace.push_back(mapSpace->space[current]);

       steps = 0; //Count side steps in case of search get stuck in a plauteal or local maximum
       while(steps<numsidesteps)
       {
            //Generate a random neighbor
            candidate = getRandomNeighbor(current,dimensions);

           //if it was found a higher point, go to it
           if(mapSpace->space[candidate]->z > mapSpace->space[current]->z)
           {
               current = candidate;
               trace.push_back(mapSpace->space[current]);
               steps=0;
           }
           //if it was found a point at same level, go to it but start counting step sides
           else if(mapSpace->space[candidate]->z == mapSpace->space[current]->z)
           {
               current = candidate;
               trace.push_back(mapSpace->space[current]);
               steps++;
           }
            //if it was not found a point at same level, compute steps, because the agent may be stuck in a maxima point
           else
           {
               steps++;
           }
       }

       //if it is the first solution found or a better solution than the old one, update the solution
       if(currSolution == NULL || currSolution->z < mapSpace->space[current]->z)
       {
           currSolution = mapSpace->space[current];
           bestSolution = current;
       }

   }
    //Return solution
   return bestSolution;

}

//Just call the search method, print and write the file
void Stochastic_Climbing::Search(Grid* mapSpace,int  numsidesteps, int repetitions)
{
    pair<int,int> solution;
    Point *currSolution;
    solution = iSearch(mapSpace,numsidesteps,repetitions);
    currSolution = mapSpace->space[solution];
    cout<<"Solution Found: "<<"x: "<<currSolution->x<<" y: "<<currSolution->y<<" z: "<<currSolution->z<<"\n";
    cout<<"Highest Z point in map: "<<mapSpace->z<<endl;
    printFile(mapSpace);
}

//Execute a performance test (percentage of correct solutions found)
void Stochastic_Climbing::performanceTest(Grid* mapSpace, int testRepetition,int sideSteps)
{
    int correctSolutions,op;
    double rate;
    pair<int,int> solution;
    correctSolutions = 0;
    list <pair<int,int> > solutionList;
    solutionList.clear();
    cout<<"1 - Stochastic Hill Climbing\n2 - Random Restart Stochastic Hill Climbing\n";
    cout<<"Option: ";
    cin>>op;
    if(!mapSpace->empty())
    {
        //srand ((time(0)));
        if(op==1)
        {

            for(int i=0;i<testRepetition;i++) //Perform N Searches (N is number of repetitions of the test)
            {

                solution = iSearch(mapSpace,sideSteps);
                solutionList.push_back(solution);
                if(mapSpace->space[solution]->z == mapSpace->z) //If a optimal solution is found, compute it
                {
                    correctSolutions++;
                }

            }

        }
        else if (op==2)
        {
            int rep;
            cout<<"Number of Restarts: ";
            cin>>rep;
            for(int i=0;i<testRepetition;i++) //Perform N Searches (N is number of repetitions of the test)
            {
                solution = iSearch(mapSpace,sideSteps,rep);
                solutionList.push_back(solution);
                if(mapSpace->space[solution]->z== mapSpace->z) //If a optimal solution is found, compute it
                    correctSolutions++;
            }

        }
    }
    else
    {
        cout<<"Please load a map before performing this operation\n\n";
    }

   rate = correctSolutions/(double)testRepetition;
   cout<<"Number of correct solutions: "<<correctSolutions<<endl;
   cout<<"Number of tests: "<<testRepetition<<endl;
   cout<<"Efficiency Rate: "<<rate*100<<"% \n";
   printFileSolutions(mapSpace,solutionList);

}
void Stochastic_Climbing::printFileSolutions(Grid *mapGrid, list <pair<int,int> > solutions)
{
     list <pair<int,int> >::iterator it;
     ofstream file;
     Point *p;
     file.open("solutions.txt");
     for(it=solutions.begin();it!=solutions.end();it++)
     {
         p = mapGrid->space[*it];
         file<<p->x<<" "<<p->y<<" "<<p->z<<"\n";
     }


     file.close();
}
