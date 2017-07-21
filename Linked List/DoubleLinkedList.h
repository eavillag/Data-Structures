#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "DoubleNode.h"

#include <stdio.h>
#include <iostream>
#include <iomanip>


using namespace std;

template <class T>
class DoubleLinkedList : public List<T>{

public:
    DoubleLinkedList() {
        cout << "Created a doubleLinkedList" << endl;
        this->SetSize(0);
        List<T>::SetHead(NULL);
        List<T>::SetTail(NULL);
    }
    //DoubleLinkedList(const DoubleLinkedList& orig);
    
    ~DoubleLinkedList() {
        try{
            Node<T>* node=this->GetHead(),*prev;
            while(node!=NULL){
                prev = node;
                cout << "Value deleted: " << prev->GetData() << endl;
                node = node->GetNext();
                delete[] prev;
            }
        }catch(const exception &e){
            throw("Destructor");
        }
    }
    
    //ACCESSORS
//    bool empty() const;
//    T front()const;
//    T back() const;   
    int count(T const &) const;
    
    //MUTATORS
    void push_front(T const &);
    void push_back(T const &);
    T pop_front();
    T pop_back();
    int erase(T const &);
    void printList();
};

//template <class T>
//bool DoubleLinkedList<T>::empty() const{
//    return List<T>::GetSize()==0;
//}
//
//template <class T>
//T DoubleLinkedList<T>::front()const{
//    try{
//        return List<T>::GetHead()->GetData();
//    }catch(const exception &e){
//        throw;
//    }
//}
//
//template <class T>
//T DoubleLinkedList<T>::back() const{
//    try{
//        return List<T>::GetTail()->GetData();
//    }catch(const exception &e){
//        throw;
//    }
//}

template <class T>
int DoubleLinkedList<T>::count(T const &t) const{
    try{
        int counter=0;
        if(!List<T>::empty()){
            Node<T> *node=List<T>::GetHead();
            while(node !=NULL){
                if(node->GetData()== t)
                    counter++;
                node = node->GetNext();
            }
        }
        return counter;
    }catch(const exception &e){
        throw("count()");
    }
}

//Mutators ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template <class T>
void DoubleLinkedList<T>::push_front(T const &val){
    try{
        DoubleNode<T> *new_node = new DoubleNode<T>(val);
        int n;
        if(!List<T>::empty()){
            new_node->SetNext(List<T>::GetHead());
            List<T>::GetHead()->SetPrevious(new_node);
        }else
            List<T>::SetTail(new_node);
        List<T>::SetHead(new_node);
        List<T>::SetSize(++(n=List<T>::GetSize()));
    }catch(const exception &e){
        throw("push_front()");
    }
}

template <class T>
void DoubleLinkedList<T>::push_back(T const &val){
    try{
        int n;
        DoubleNode<T> *new_node = new DoubleNode<T>(val);
        if(!this->empty()){
            new_node->SetPrevious(this->List<T>::GetTail());
            this->List<T>::GetTail()->SetNext(new_node);
        }else
            List<T>::SetHead(new_node);
        List<T>::SetTail(new_node);
        List<T>::SetSize(++(n=List<T>::GetSize()));
    }catch(const exception &e){
        throw("push_back()");
    }
}
template <class T>
T DoubleLinkedList<T>::pop_front(){
    try{
        if(this->empty())
            cout << "Error. List is empty. Could not pop_front()" << endl;
        else{
            int n;
            T new_val=List<T>::GetHead()->GetData();
            List<T>::SetHead(List<T>::GetHead()->GetNext());
            if((n=List<T>::GetSize())-- >1){ //more than 1
                delete []List<T>::GetHead()->GetPrevious();
                List<T>::GetHead()->SetPrevious(NULL);
            }
            else{//only 1
                delete[] List<T>::GetTail();
                List<T>::SetTail(NULL);
            }
            List<T>::SetSize(n);
            return new_val;
        }
        return -1;
    }catch(const exception &e){
        throw("pop_front()");
    }
}

template<class T>
T DoubleLinkedList<T>::pop_back(){
    try{
        if(this->empty())
            cout << "Error. List is empty. Could not pop_back()" << endl;
        else{
            int n;
            T new_val=List<T>::GetTail()->GetData();
            List<T>::SetTail(List<T>::GetTail()->GetPrevious());
            if((n=List<T>::GetSize())-- >1){
                delete [] List<T>::GetTail()->GetNext();
                 List<T>::GetTail()->SetNext(NULL);
            }
            else{
                delete []List<T>::GetHead();   
                List<T>::SetHead(NULL);
            }
            List<T>::SetSize(n);
            return new_val;
        }
        return -1;
    }catch(const exception &e){
        throw("pop_back()");
    }
}


template <class T>
int DoubleLinkedList<T>::erase(T const &val){
    try{
        int counter=0,n;
        if(!this->empty()){
            while(List<T>::GetHead()->GetData() == val)
                pop_front();
            while(List<T>::GetTail()->GetData() == val)
                pop_back();
            if(List<T>::GetSize() > 1){
                Node<T> *current=List<T>::GetHead()->GetNext(),*last = List<T>::GetTail(),*prev=List<T>::GetHead(),*temp;
                while(current != last){
                    if(val == current->GetData()){
                        temp = current;
                        current = current->GetNext();
                        prev->SetNext(current);
                        current->SetPrevious(prev);
                        delete[] temp;
                        counter++;
                        List<T>::SetSize(--(n=List<T>::GetSize()));
                    }else{
                        prev = current;
                        current = current->GetNext();
                    }
                }
            }
        }else
            cout << "List empty." << endl;
        return counter;
    }catch(const exception &e){
        throw("erase()");
    }
}

template<class T>
void DoubleLinkedList<T>::printList(){
    Node<T> *current = List<T>::GetHead();
    while(current != NULL){
        cout << setw(5)<<current->GetData();
        current = current->GetNext();
    }
    cout << endl;
}


#endif /* DOUBLELINKEDLIST_H */

