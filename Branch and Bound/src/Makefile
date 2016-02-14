objs = main.o branch.o t_graph.o

Program: $(objs)
	g++ -o dyn-branch-search $(objs)

main.o: t_graph.h astar.h main.cpp
	g++ -c main.cpp

branch.o: t_graph.h branch.h branch.cpp
	g++ -c branch.cpp

t_graph.o: t_graph.h t_vertex.h t_edge.h t_graph.cpp
	g++ -c t_graph.cpp

clean:
	rm $(objs)
