/*************************************************/
/*    Graph Class using an adjacent linked list  */
/*        developed by Gabriel Augusto           */
/*            Date: 23/03/2014                   */
/*          gabriel301@gmail.com                 */
/*************************************************/

#include "t_graph.h"
#include <iostream>
#include <cstddef>
#include <fstream>
using namespace std;

//Clear graph (Delete all nodes of the linked list)
/*This method take the a node,delete all of its edges and the delete the node.
 The first node is the head one*/
void t_graph::clear()
{
    t_vertex *auxV;
    t_edge *auxE;
    while(this->head)
    {
        while(this->head->edges)
        {
            auxE = this->head->edges->nextEdge;
            delete this->head->edges;
            this->head->edges =auxE;
        }
        auxV = this->head->nextVertex;
        delete this->head;
        this->head = auxV;
    }
}

 //Clear flags (parent and visited) of each node
void t_graph::clearFlags()
{
    t_vertex *auxV = this->head;
    while(auxV!=NULL)
    {
        auxV->parent = NULL;
        auxV->visited = false;
        auxV = auxV->nextVertex;
    }
}

//Constructor
t_graph::t_graph()
{
    this->head = NULL;
    this->current = NULL;
}


//Verify whether a vertex exists in the graph
/*This method searches in the linked list whether a vertex exists or not.
  If it exists, return a its reference, else return NULL*/
struct t_vertex *t_graph::vertexExists(int v)
{
    t_vertex *next;
    next = this->head;
    while (next)
    {
        if(next->label == v)
        {
            return next;
        }

        next = next->nextVertex;
    }
    return NULL;
}

//Add a node in the  linked list
/*This method adds a node in the end of the linked list*/
void t_graph::addVertex(t_vertex *v)
{
    t_vertex *aux;
    if(this->head == NULL)
    {
        head = v;
    }

    else
    {
        aux = this->head;
        while (aux->nextVertex)
        {
            aux = aux->nextVertex;
        }
        aux->nextVertex = v;
    }

}


//Add an Undirected Edge (add 2 edges: Parent->Child and Child->Parent)
/*This method does not allow repetition of nodes, i.e. if a node with label
X is already on the graph, it does not add a new node X*/
void t_graph::addUndirectedEgde(int v1, int v2,double w)
{
    t_vertex *auxV;
    t_edge *auxE;

    //Verify if V1 exists in graph
    this->current = this->vertexExists(v1);

    //If V1 does not exist in the graph, it is added to the linked list
    if(this->current == NULL)
    {
        auxV = new t_vertex(v1);
        this->addVertex(auxV);
        this->current = auxV;  //Set V1 as the current node (for adding the edge)
    }

   //Verify if V1 exists in graph
    auxV = this->vertexExists(v2);

    //If V2 does not exist in the graph, it is added to the linked list
    if(auxV==NULL)
    {
        auxV = new t_vertex(v2);
        this->addVertex(auxV);
    }

    //Add edge V1->v2 in V1's edge list
    //If it is the first Edge, Add the edge
    if(this->current->edges==NULL)
    {
        this->current->edges = new t_edge(w);
        this->current->edges->connection = auxV;
    }
    else //If it is not the first Edge, it goes to the end of edge list and then add the new edge
    {
        auxE = this->current->edges;
        while(auxE->nextEdge)
        {
            auxE = auxE->nextEdge;
        }
        auxE->nextEdge = new t_edge(w);
        auxE->nextEdge->connection = auxV;
    }


    //Add edge V2->V1 in V2's edge list
    //If it is the first Edge, Add the edge
    if(auxV->edges==NULL)
    {
        auxV->edges = new t_edge(w);
        auxV->edges->connection = this->current;
    }
    else //If it is not the first Edge, it goes to the end of edge list and then add the new edge
    {
        auxE = auxV->edges;
        while(auxE->nextEdge)
        {
            auxE = auxE->nextEdge;
        }
        auxE->nextEdge = new t_edge(w);
        auxE->nextEdge->connection = this->current;
    }
}

 //Add a Directed Edge (add 1 edge: Parent->Child)
/*This method does not allow repetition of nodes, i.e. if a node with label
X is already on the graph, it does not add a new node X*/
void t_graph::addDirectedEgde(int v1, int v2,double w)
{
    t_vertex *auxV;
    t_edge *auxE;
    //Verify if V1 exists in graph
    this->current = this->vertexExists(v1);

   //If V1 does not exist in the graph, it is added to the linked list
    if(this->current == NULL)
    {
        auxV = new t_vertex(v1);
        this->addVertex(auxV);
        this->current = auxV; //Set V1 as the current node (for adding the edge)
    }

    //Verify if V2 exists in graph
    auxV = this->vertexExists(v2);

    //If V2 does not exist in the graph, it is added to the linked list
    if(auxV==NULL)
    {
        auxV = new t_vertex(v2);
        this->addVertex(auxV);
    }

     //Add edge V1->V2 in V1's edge list
    //If it is the first Edge, Add the edge
    if(this->current->edges==NULL)
    {
        this->current->edges = new t_edge(w);
        this->current->edges->connection = auxV;
    }
    else //If it is not the first Edge, it goes to the end of edge list and then add the new edge
    {
        auxE = this->current->edges;
        while(auxE->nextEdge)
        {
            auxE = auxE->nextEdge;
        }
        auxE->nextEdge = new t_edge(w);
        auxE->nextEdge->connection = auxV;
    }
}

t_graph::~t_graph()
{
    this->clear();
}

//Print Graph Information
/*This method visits each node of the linked list and print its information (label, edges etc)*/
void t_graph::print()
{

    t_vertex *auxV;
    t_edge *auxE;
    auxV = this->head;

    while(auxV)
    {

        auxE = auxV->edges;
        cout<<(char)auxV->label<<": ";
        while(auxE)
        {
            cout<<"|V: "<<(char)auxE->connection->label<<",W: "<<auxE->weight<<"| ";
            auxE = auxE->nextEdge;

        }
        cout<<"\n";
        auxV = auxV->nextVertex;
    }

    cout<<"\nHeuristic Costs\n";
    auxV = this->head;
    while(auxV)
    {
        cout<<(char)auxV->label<<" "<<auxV->h<<"\n";
        auxV = auxV->nextVertex;

    }

}

//Write Graph Information in a file
/*This method visits each node of the linked list and print its information (label, edges etc)*/
void t_graph::printFile()
{
    ofstream file;
    t_vertex *auxV;
    t_edge *auxE;
    auxV = this->head;
    file.open("graph-printed.txt");
    while(auxV)
    {

        auxE = auxV->edges;
        while(auxE)
        {
            file<<(char)auxV->label<<" "<<(char)auxE->connection->label<<" "<<auxE->weight<<"\n";
            auxE = auxE->nextEdge;

        }
        auxV = auxV->nextVertex;
    }
    file<<"\nHeuristic Costs\n";
    auxV = this->head;
    while(auxV)
    {
        file<<(char)auxV->label<<" "<<auxV->h<<"\n";
        auxV = auxV->nextVertex;
    }
    file.close();
}

//Read heuristic information
/*This method finds the node and add heuristic information*/
void t_graph::addHeristicCost(int v, double cost)
{
    t_vertex *p;
    p = this->vertexExists(v);
    if(p!=NULL)
        p->h = cost;
}

//Add a Directed Edge (add 1 edge: Parent->Child)
/*This method does allows repetition of nodes, i.e. if a node with label
X is already on the graph, you can add other node with same label
This method is used by search algorithms build the search tree */
void t_graph::addTreeEgde(struct t_vertex *v1, struct t_vertex *v2 , double w)
{
    t_edge *auxE;

    //Set V1 as the current node (for adding the edge)
    this->current = v1;

    //Add edge V1->V2 in V1's edge list
    //If it is the first Edge, Add the edge
    if(this->current->edges==NULL)
    {
        this->current->edges = new t_edge(w);
        this->current->edges->connection = v2;
    }
    else //If it is not the first Edge, it goes to the end of edge list and then add the new edge
    {
        auxE = this->current->edges;
        while(auxE->nextEdge)
        {
            auxE = auxE->nextEdge;
        }
        auxE->nextEdge = new t_edge(w);
        auxE->nextEdge->connection = v2;
    }

    //Set V1 as parent of V2 (for retrieving the path later)
    v2->parent = v1;
}

//Verify whether graph is empty
bool t_graph::empty()
{
    return this->head==NULL;
}


