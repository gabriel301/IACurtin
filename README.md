# IACurtin
Implementation of the A-Star, Branch and Bound, and Stichastic hill climbing algorithms as an assignment of the subject Artificial and Machine Intelligence 300 from Curtin University, Semester 1 2014.
## Assignment
### PART 1 - Informed search strategy implementation
You are required to implement the A* search and the branch and bound with dynamic programming search strategies for finding the path between two user specified nodes in an undirected graph. Please note that the branch and bound search with dynamic programming is different from the “classic” branch and bound search in the sense that it will be more memory efficient.  
The implementation should handle general graphs.  
For both searches, the program should prompt the user for the start and end node
in the graph (or alternatively, the user can specify the start/goal nodes via command line
arguments). The program should then return the solution path between the two nodes as
well as a list of the alternative solutions and partial paths.  
  
### PART 2 - Local Search Strategy Implementation
You are required to implement an agent that performs the stochastic hill climbing
search.  
The implementation should handle all 3D maps where the map information is provided in the form of a sequence of x, y, z values. The size of the map will not be known – you can only assume that the map information is complete (there will always be
x, y and z values provided for each point on the map).  
The program should prompt the user for the name of the file containing the map and return the following:  
1) the highest elevation point on the map (the point with the highest z value)
2) the sequence of points visited to reach the highest point on the map – the sequence of points should be saved in a file called seq.txt, and the format should be exactly as the map file (text format containing the x, y, z coordinates visited in the exact order that the agent used to explore the map).  
You will be provided with a sample map to test your program. However, you are expected to test your program with other 3D maps in order to be able to accurately evaluate its performance on general 3D maps.  
Finally, if you wish to display the map you can use the gnuplot program. You will need to use the splot function to plot the points
contained in the map file as shown in the example below (assuming that you are already
running gnuplot and the file map1.txt is in the current directory):  
>splot “map1.txt” with points
