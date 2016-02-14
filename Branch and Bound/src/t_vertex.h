/*************************************************/
/*    t_vertex type developed by Gabriel Augusto   */
/*            Date: 23/03/2014                   */
/*          gabriel301@gmail.com                 */
/*************************************************/

#ifndef T_VERTEX_H_INCLUDED
#define T_VERTEX_H_INCLUDED
#include "t_edge.h"
#include <cstddef>
#include <iostream>
using namespace std;
struct t_edge;

struct t_vertex
{
    int label; //Vertex's Label
    double h,g,f; //Heuristic cost, accumulated path cost and estimated cost
    t_vertex *nextVertex; //Pointer to Next vertex in the Linked list
    t_edge *edges; //Pointer to first edge of this node
    bool visited; //Flag to check if current vertex have been visited by search method (explored);
    t_vertex *parent;  //Reference to vertex's parent (It's a way to find the path)
    t_vertex(int v) //Constructor
    {
        this->label = v;
        this->nextVertex = NULL;
        this->edges = NULL;
        this->visited = false;
        this->h = 0;
        this->g = 0;
        this->f = 0;
        this->parent = NULL;
    }

    //Copy Constructor
    t_vertex(struct t_vertex *v)
    {
        this->label = v->label;
        this->nextVertex = NULL;
        this->edges = NULL;
        this->visited = false;
        this->h = v->h;
        this->g = v->g;
        this->f = v->f;
        this->parent = NULL;
    }
};

#endif // T_VERTEX_H_INCLUDED
