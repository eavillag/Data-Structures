CC = g++
CFLAGS  = -g -Wall

default: doubleLinkedList

doubleLinkedList: menu.cpp DoubleLinkedList.h DoubleNode.h CyclicLinkedList.h SingleNode.h List.h Node.h
	$(CC) $(CFLAGS)  -o LinkedList menu.cpp

clean: 
	$(RM) count *.o *~
