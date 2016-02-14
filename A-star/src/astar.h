/*************************************************/
/*    A-Star Search developed by Gabriel Augusto */
/*            Date: 05/04/2014                   */
/*          gabriel301@gmail.com                 */
/*************************************************/

#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED
#include <map>
#include <vector>
#include "t_graph.h"
using namespace std;


class Astar
{
private:
    multimap<double, struct t_vertex *> opened, closed; //Sets of opened and closed paths in the search
    vector<struct t_vertex *> solutions; //Set of solution paths
    t_graph searchTree; //Search tree
public:
    //A-Star search
    void Search(struct t_graph*,int, int);

    //Print solutions
    void PrintSolutions();
    //Print Partial paths
    void PrintPartialPaths(int, double);

    //Clear Search tree, solution set, opened and closed sets
    void Clear();
};

#endif // ASTAR_H_INCLUDED
