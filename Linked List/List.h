
#ifndef LIST_H
#include <stdio.h>
#include <iostream>

using namespace std;

template<class T> class Node;

template<class T>
class List {
    int size;
    Node<T> *head;
    Node<T> *tail;
public:
    
//    List(){
//    }
//    List(const List& orig){
//
//    }
//    ~List(){
//        delete head;
//        delete tail;
//    }

    void SetTail(Node<T>* tail);
    Node<T>* GetTail() const;
    
    void SetHead(Node<T>* head);
    Node<T>* GetHead() const;
    
    void SetSize(int size);    
    int GetSize() const;    
    
    bool empty() const;
    T front() const;
    T back() const;
    //VIRTUAL METHODS--------------------------------------------------------->
//    virtual bool empty() const=0;
//    virtual T front()const=0;
//    virtual T back() const=0;   
    virtual int count(T const &) const=0;
    
    //MUTATORS
    virtual void push_front(T const &)=0;
    virtual void push_back(T const &)=0;
    virtual T pop_front()=0;
    virtual T pop_back()=0;
    virtual int erase(T const &)=0;
    
    virtual void printList()=0;

};

template <class T>
Node<T>* List<T>::GetTail() const {
    return this->tail;
}

template <class T>
Node<T>* List<T>::GetHead() const {
    return this->head;
}

template <class T>
int List<T>::GetSize() const {
    return this->size;
}

template <class T>
void List<T>::SetTail(Node<T>* tail) {
    try{
        this->tail=tail;
    }catch(const exception &e){
        throw("SetTail");
    }
}

template <class T>
void List<T>::SetHead(Node<T>* head) {
    try{
        this->head = head;
    }catch(const exception &e){
        throw("SetHead()");
    }
}

template <class T>
void List<T>::SetSize(int size) {
    try{
        if(size >= 0)
            this->size = size;
        else
            cout << "Error value" << endl;
    }catch(const exception &e){
        throw("SetSize()");
    }
}

template <class T>
bool List<T>::empty() const{
    return GetSize()==0;
}

template <class T>
T List<T>::front()const{
    try{
        if(!empty())
            return GetHead()->GetData();
        else
            cout<< "Exception. List empty" << endl;
    }catch(const exception &e){
        throw;
    }
}

template <class T>
T List<T>::back() const{
    try{
        if(!empty())
            return GetTail()->GetData();
        else
            cout<< "Exception. List empty" << endl;
    }catch(const exception &e){
        throw;
    }
}

#endif /* LIST_H */

