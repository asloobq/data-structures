CXX = gcc
CFLAGS = -g -Wall -Wextra -pedantic

all: graph1

graph1: graph1.o
	$(CXX) $(CFLAGS) -o graph1 graph1.o

graph1.o: graph1.c
	$(CXX) $(CFLAGS) -c graph1.c

clean:
	rm *.o graph1 
