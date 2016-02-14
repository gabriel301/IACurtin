/*************************************************/
/*    Graph Class developed by Gabriel Augusto   */
/*            Date: 23/03/2014                   */
/*          gabriel301@gmail.com                 */
/*************************************************/

/*Graph data structure implemented as a linked adjacency list*/

#ifndef T_GRAPH_H_INCLUDED
#define T_GRAPH_H_INCLUDED
#include "t_edge.h"
#include "t_vertex.h"
class t_graph
{
    public:
      //Head pointer of the linked list
      t_vertex *head;

      //Point to perform some operations
      t_vertex *current;

      //Constructor
      t_graph();

      //Destructor
      ~t_graph();

      //Add an Undirected Edge (add 2 edges: Parent->Child and Child->Parent)
      /*This method does not allow repetition of nodes, i.e. if a node with label
       X is already on the graph, it does not add a new node X*/
      void addUndirectedEgde(int,int,double);

      //Add a Directed Edge (add 1 edge: Parent->Child)
      /*This method does not allow repetition of nodes, i.e. if a node with label
       X is already on the graph, it does not add a new node X*/
      void addDirectedEgde(int,int,double);

      //Print Graph Information
      void print();

      //Write Graph Information in a file
      void printFile();

      //Verify whether a vertex exists in the graph
      struct t_vertex *vertexExists(int);

      //Clear graph (Delete all nodes of the linked list)
      void clear();

      //Clear flags (parent and visited)
      void clearFlags();

      //Read heuristic information
      void addHeristicCost(int, double);

      //Add a Directed Edge (add 1 edge: Parent->Child)
      /*This method does allows repetition of nodes, i.e. if a node with label
       X is already on the graph, you can add other node with same label
       This method is used by search algorithms build the search tree */
      void addTreeEgde(struct t_vertex *, struct t_vertex * , double);

      //Add a node in the linked list;
      void addVertex(t_vertex*);

      //Verify whether graph is empty
      bool empty();
};


#endif // T_GRAPH_H_INCLUDED
