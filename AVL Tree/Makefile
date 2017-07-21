CC = g++
CFLAGS = -c -g -Wall
LFLAGS  = -g -Wall
CXXFLAGS := -std=c++0x

default: dynamicStackQueue

dynamicStackQueue: menu.cpp linkedTree.o avlTree.o treeNode.o 
	$(CC) $(LFLAGS) $(CXXFLAGS) -o project3 menu.cpp

linkedTree.o : linkedTree.h treeNode.h
	$(CC) $(CFLAGS) $(CXXFLAGS) linkedTree.h

avlTree.o : avlTree.h treeNode.h linkedTree.h
	$(CC) $(CFLAGS) $(CXXFLAGS) alvTree.h

treeNode.o : treeNode.h
	$(CC) $(CFLAGS) $(CXXFLAGS) treeNode.h
clean: 
	$(RM) count *.o *.gch
