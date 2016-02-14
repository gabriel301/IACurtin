/*************************************************/
/*    Branch and Bound with Dynamic Programming  */
/*        developed by Gabriel Augusto           */
/*            Date: 05/04/2014                   */
/*          gabriel301@gmail.com                 */
/*************************************************/

#include "branch.h"
#include <iostream>
#include <stack>
using namespace std;

//Branch and Bound search
void Branch_and_Bound::Search(struct t_graph *graph, int start, int goal)
{

	t_vertex *auxV1, *auxV2;
	t_edge *auxE;
	bool skip; //Flag to skip the node (do not put it in opened paths list)
	multimap<double,struct t_vertex *>::iterator it;
    double currentCost; //Current solution cost

    this->Clear();

	auxV1 = new t_vertex(graph->vertexExists(start)); //Set the goal node
	auxV1->f = auxV1->g; // Calculation of F(n) (F = G)

	//Add the parent node in the tree
	searchTree.addVertex(auxV1);

	opened.insert(pair<double,struct t_vertex *> (auxV1->f,auxV1)); //Put the current node in opened list
    //If the initial node is not the goal node, perform the search
    if(auxV1->label != goal)
    {
        while(!opened.empty())
        {

            auxV1 = opened.begin()->second; //Take the less F(n) node (maps are ordered)

            opened.erase(opened.begin()); // put this node off of the opened list


                auxE = graph->vertexExists(auxV1->label)->edges; //Take the edges of current node in the graph


                while(auxE != NULL)
                {
                    skip = false;
                    //Reject paths w/ loops (expanding parents)
                    if(auxE->connection !=NULL && auxV1->parent != NULL)
                    {
                        if(auxE->connection->label == auxV1->parent->label)
                        {
                             auxE = auxE->nextEdge;
                             continue;
                        }
                    }

                    //Add the child node in search tree
                    auxV2 = new t_vertex(auxE->connection);

                    //Calculation of accumulated cost
                    auxV2->g = auxV1->g + auxE->weight;
                    auxV2->f =  auxV2->g;

                    //Add the child node in the tree
                    searchTree.addVertex(auxV2);

                    //Add the edge Parent->child in search tree
                    searchTree.addTreeEgde(auxV1,auxV2,auxE->weight);


                    /*If the current node is the goal node, put it on the set of solutions
                    (if the path is lower than the current solution or equal to current solution or solution set is empty)*/
                    if(auxV2->label==goal)
                    {
                        if(solutions.empty())
                        {
                            currentCost = auxV2->g;
                            solutions.push_back(auxV2);
                        }
                        else
                        {
                            //If the solution found is better than the older solution, replace the solution;
                            //If the new solution has same cost of another in the set, just add the new one in the set
                            if(auxV2->g <= currentCost)
                            {
                                for(unsigned int i=0;i<solutions.size();i++)
                                {
                                    if(auxV2->g < solutions[i]->g)
                                    {
                                        solutions.erase(solutions.begin()+i);
                                    }
                                }
                            solutions.push_back(auxV2);
                            currentCost = auxV2->g;
                           }
                        }
                        skip = true;
                    }

                    //If the current node is not the goal, but there is a path to goal that is lower than
                    //the path through the current neighbor, discard this path
                    if(solutions.size()>0)
                    {
                        if(auxV2->g > currentCost)
                        {
                            skip = true;
                        }

                    }


                    //If there was a visited path which reaches at the same node and it is lower than the path through the current node
                    //discard this path
                    for(it=closed.begin();it!= closed.end();it++)
                    {
                        if(it->second->label == auxV2->label && it->second->g < auxV2->g)
                        {
                            skip = true;
                            break;
                        }
                    }


                        for(it=opened.begin();it!= opened.end();)
                        {
                             /*If there is an opened path which reaches at the same node and it is lower than the path through the current node
                             discard this path*/
                            if(it->second->label == auxV2->label && it->second->g < auxV2->g)
                            {
                                skip = true;
                                ++it;
                            }

                             //If there is an opened path which reaches at the same node and it is longer than the path through the current
                            //discard the old path. If the current node is a goal node and the path that reaches it is lower than any paths
                            //opened, discard these paths
                            else if(it->second->label == auxV2->label && it->second->g > auxV2->g || (auxV2->label == goal && it->second->g > auxV2->g))
                            {
                                closed.insert(pair<double,struct t_vertex *> (it->second->g,it->second));
                                multimap<double,struct t_vertex *>::iterator erase;
                                erase = it;
                                ++it;
                                opened.erase(erase);
                            }
                            else
                            {
                                ++it;
                            }


                        }



                    if(!skip)
                    {
                        //Include the new path in opened list
                        opened.insert(pair<double,struct t_vertex *> (auxV2->g,auxV2));
                    }
                    else
                    {
                        //Include the new path in closed list (it was marked as "To skip"
                        closed.insert(pair<double,struct t_vertex *> (auxV2->g,auxV2));
                    }

                    auxE = auxE->nextEdge;

            }
            //Insert the parent node into the closed paths list
            closed.insert(pair<double,struct t_vertex *> (auxV1->g,auxV1));

        }
    }
    else //if the initial node is the goal node, include it in the solution set
    {
        currentCost = auxV1->g;
        solutions.push_back(auxV1);
    }
	cout<<"****SOLUTIONS*****\n";
	this->PrintSolutions();

	cout<<"\n****PARTIAL PATHS*****\n";
	this->PrintPartialPaths(goal, currentCost);

}

//Print Partial paths
void Branch_and_Bound::PrintPartialPaths(int goal, double costSolution)
{
	t_vertex *aux;
	double cost;
	int i=0;
	stack <int> path; //stack to store the path
	multimap<double,struct t_vertex *>::iterator it;

    /*Search it closed set the leaf-nodes (either partial paths explored or non-optimal solutions found)
    and retrieve the path by parent pointer*/
        for(it=closed.begin();it!= closed.end();it++)
        {
            aux = it->second;
            cost = aux->g;
            if(aux->edges==NULL && ((aux->label != goal) || (aux->label == goal && aux->g >costSolution)))
            {
                //Put the path in a stack for displaying it in the right order
                while (aux)
                {
                    path.push(aux->label);
                    aux = aux->parent;
                }
                cout<<"Path: "<<i+1<<" - "<<"Cost: "<<cost<<"\n";

                //Display the path
                while(!path.empty())
                {
                    cout<<(char)path.top()<<" -> ";
                    path.pop();
                }
                i++;
                cout<<"\n\n";
            }

        }
        if(i==0)
          cout<<"No Paths Found\n\n";


}

//Print solutions
void Branch_and_Bound::PrintSolutions()
{
    t_vertex *aux;
	double cost;
	stack <int> path; //stack to store the path
	if(solutions.size()==0)
        cout<<"No Solutions Found\n\n";
	else
    {
        /* Retrieve the solutions path by parent pointer*/
        for(unsigned int i=0;i<solutions.size();i++)
        {

            aux = solutions[i];
            cost = aux->g;

            //Put the path in a stack for displaying it in the right order
            while (aux)
            {
                path.push(aux->label);
                aux = aux->parent;
            }

            cout<<"Path: "<<i+1<<" - "<<"Cost: "<<cost<<"\n";
            //Display the path
            while(!path.empty())
            {
                cout<<(char)path.top()<<" -> ";
                path.pop();
            }
            cout<<"\n\n";
        }
    }
}

//Clear Search tree, solution set, opened and closed sets
void Branch_and_Bound::Clear()
{
    searchTree.clear();
    solutions.clear();
    opened.clear();
    closed.clear();
}
