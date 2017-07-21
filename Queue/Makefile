CC = g++
CFLAGS = -c -g -Wall
LFLAGS  = -g -Wall
CXXFLAGS := -std=c++0x

default: project2

project2: menu.cpp stack.o queue.o
	$(CC) $(LFLAGS) $(CXXFLAGS) -o project2 menu.cpp

stack.o : stack.h
	$(CC) $(CFLAGS) $(CXXFLAGS) stack.h

queue.o : queue.h
	$(CC) $(CFLAGS) $(CXXFLAGS) queue.h
clean:
	$(RM) count *.o *.gch
