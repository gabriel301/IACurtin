objs = main.o astar.o t_graph.o

Program: $(objs)
	g++ -o astar-search $(objs)

main.o: t_graph.h astar.h main.cpp
	g++ -c main.cpp

astar.o: t_graph.h astar.h astar.cpp
	g++ -c astar.cpp

t_graph.o: t_graph.h t_vertex.h t_edge.h t_graph.cpp
	g++ -c t_graph.cpp

clean:
	rm $(objs)
