#ifndef NODE_H
#define NODE_H

#include <stdio.h>

template <class T> class List;

template <class T>
class Node {
   
public:
    T data;
    Node<T> *next;
    Node<T> *previous;
    
    friend class List<T>;
    
    virtual void SetNext(Node<T>* next)=0;
    virtual Node<T>* GetNext() const=0;
    
    virtual void SetData(T data)=0;
    virtual T GetData() const=0;
    
    void SetPrevious(Node<T>* previous);
    Node<T>* GetPrevious() const;
    virtual void Print()=0;
    
};
template<class T>
void Node<T>::SetPrevious(Node<T>* previous) {
    this->previous = previous;
}

template<class T>
Node<T>* Node<T>::GetPrevious() const {
    return previous;
}

#endif /* NODE_H */

