#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H
#include <iostream>
#include <stdlib.h>

#include "Node.h"

template <class T> class CyclicLinkedList;

template <class T>
class SingleNode : public Node<T>
{
    public:

        // Class Constructor
        SingleNode(const T & d, SingleNode *n)
        {
            SetData(d);
            SetNext(n);
        }

        SingleNode(const SingleNode& n);

        // Class Destructor
        ~SingleNode()
        {
            std::cout << "Node with data: " << GetData() << " is being deleted" << std::endl;
        }

        // Accessors
        void Print();

        // Member Getter/Setters
        T GetData() const;
        void SetData(T);
        Node<T>* GetNext() const;
        void SetNext(Node<T>* n);


        // CyclicLinkedList is a friend of this class
        friend class CyclicLinkedList<T>;
};


// Returns data in the current node
template<class T>
T SingleNode<T>::GetData() const
{
    return this->data;
}

template<class T>
void SingleNode<T>::SetData(T d)
{
    this->data = d;
}


// Returns pointer to the next node
template<class T>
Node<T>* SingleNode<T>::GetNext() const
{
    return this->next;
}

template<class T>
void SingleNode<T>::SetNext(Node<T>* n)
{
    this->next = n;
}

// Prints the data in the node
template<class T>
void SingleNode<T>::Print()
{
    std::cout << this->data << "\t";
}

#endif