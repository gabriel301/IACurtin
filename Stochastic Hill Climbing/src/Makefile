objs = main.o grid.o 

Program: $(objs)
	g++ -o stochastic-hill $(objs)

main.o: grid.h main.cpp
	g++ -c main.cpp

grid.o: grid.h grid.cpp
	g++ -c grid.cpp

clean:
	rm $(objs)