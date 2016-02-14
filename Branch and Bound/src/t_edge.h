/*************************************************/
/*    t_edge type developed by Gabriel Augusto   */
/*            Date: 23/03/2014                   */
/*          gabriel301@gmail.com                 */
/*************************************************/

#ifndef T_EDGE_H_INCLUDED
#define T_EDGE_H_INCLUDED
#include "t_vertex.h"
struct t_edge
{
    double weight; //Edge's Weight
    t_vertex *connection; //Pointer to next vertex connected
    t_edge *nextEdge;// Pointer to next edge

    t_edge(int w)
    {
        this->connection = NULL;
        this->nextEdge = NULL;
        this->weight = w;
    }
};

#endif // T_EDGE_H_INCLUDED
