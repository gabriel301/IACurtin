#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#include <map>
#include <utility>
#include <string>
#include <list>
using namespace std;

//Point Struct
struct Point
{
    double x,y,z;

    Point(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }
};

class Grid
{
    private:
         pair<int,int> pts;
         void createShoulderMap(); //Create a file  containing a map with shoulders
         void createOnePickMap(); //Create a file containing a map with one pick
         void createMultiLocalMaxima(); //Create a file containing a map with multiple local maxima
         void createMultiplePicks(); //Create a file containing a map with multiple picks
         void createRandomMap(); //Create a file  containing a map with random points
    public:
        //Structure to store the map
        map<pair<int,int>,struct Point*> space;

        //Highest value of z in the map (to compare with solution found
        double z;

        //Load a map from file
        void loadMap(string);

        //Erases a map from memory
        void clearMap();

        //Write the loaded map in a file
        void printFile();

        //Get the dimensions of the loaded map
        pair<int,int> getDimensions();

        //Verify whether a map is load in memory
        bool empty();

        //Create one of maps described above (in private part)
        void createMap();

};

class Stochastic_Climbing
{
    private:
      list<struct Point *> trace; //List to store the points that search visited

      pair<int,int> iSearch(Grid*,int,int repetitions = 1); /*Search method. Repetition param has a default value 1
                                                            (it means it will be performed Stochastic Hill Climbing).
                                                            If other value is passed as param, a Random Restart Stochastic Hill Climbing
                                                            will be performed (Repetitions = number of restarts of searching)*/

    public:

      //Call the search function and print the results
      void Search(Grid*,int,int repetitions = 1);

      //Write the sequence of visited points in a file
      void printFile(Grid *);

      //clear the list of visited points
      void clear();

      //Generates one neighbor of the current point randomly
      pair<int,int> getRandomNeighbor(pair<int,int>,pair<int,int>);

      //Execute a performance test (percentage of correct solutions found)
      void performanceTest(Grid*,int,int);

      //Print a set of solutions in a file
      void printFileSolutions(Grid *, list <pair<int,int> >);
};
#endif // GRID_H_INCLUDED
