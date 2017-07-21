#ifndef DOUBLENODE_H
#define DOUBLENODE_H

#include <stdio.h>
#include <iostream>
#include "Node.h"

using namespace std;

template <class T> class DoubleLinkedList;

template <class T>
class DoubleNode : public Node<T>{   

public:
    DoubleNode(T const &d, DoubleNode<T>* p=NULL, DoubleNode<T>* n=NULL){
        SetNext(n);
        SetPrevious(p);
        SetData(d);
    }
    DoubleNode(const DoubleNode& orig);
    //virtual ~DoubleNode();
    
    void SetPrevious(Node<T>* previous);
    void SetNext(Node<T>* next);
    void SetData(T data);
    
    friend class DoubleLinkedList<T>;
    Node<T>* GetPrevious() const;
    Node<T>* GetNext() const;
    T GetData() const;
    void Print();
};


template<class T>
DoubleNode<T>::DoubleNode(const DoubleNode<T>& orig) {
}

//ACCESSORS ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
template<class T>
Node<T>* DoubleNode<T>::GetPrevious() const {
    return this->previous;
}

template<class T>
Node<T>* DoubleNode<T>::GetNext() const {
    return this->next;
}

template<class T>
T DoubleNode<T>::GetData() const {
    return this->data;
}

//PRIVATE ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
template<class T>
void DoubleNode<T>::SetPrevious(Node<T>* previous) {
    this->previous = previous;
}

template<class T>
void DoubleNode<T>::SetNext(Node<T>* next) {
    this->next = next;
}
template<class T>
void DoubleNode<T>::SetData(T data) {
    this->data = data;
}

template<class T>
void DoubleNode<T>::Print(){
    cout << "TIBS" <<endl;
}
#endif /* DOUBLELINKEDNODE_H */

