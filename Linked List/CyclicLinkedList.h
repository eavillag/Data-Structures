#ifndef CYCLIC_LINKED_LIST_H
#define CYCLIC_LINKED_LIST_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "SingleNode.h"


template <class T>
class CyclicLinkedList: public List<T>{
 //   private:
//        int size;
//        SingleNode<T> *headPtr;
//        SingleNode<T> *tailPtr;
    int pop( T const &val);
public:
    // Class Constructor
    CyclicLinkedList()    {
        cout << "Created a cyclicLinkedList" << endl;
        List<T>::SetSize(0);
        List<T>::SetHead(NULL);
        List<T>::SetTail(NULL);
    }


    // Class Destructor
    ~CyclicLinkedList(){
        std::cout << "Cyclic List is being deleted" << std::endl;

        Node<T> *current = List<T>::GetHead(), *temp;
        if(List<T>::empty())
            return;

        do {
            temp = current;
            current = current->GetNext();
            delete temp;
        } while(current != List<T>::GetHead());
    }

    //Accessors
//    bool empty() const;
//    T front() const;
//    T back() const;
    int count(T const &val) const;
    void printList();

    //Mutators
    void push_front(T const &val);
    void push_back(T const &val);
    T pop_front();
    T pop_back();
    int erase(T const &val);
};

//// Tells us whether the list is empty or not
//template <class T>
//bool CyclicLinkedList<T>::empty() const
//{
//    if (List<T>::GetSize() == 0)
//        return true;
//    else
//        return false;
//}
//
//// Returns the data in the top node of the list
//template <class T>
//T CyclicLinkedList<T>::front() const
//{
//    return List<T>::GetHead()->GetData();
//}
//
//
//// Returns the data in the tail of the list
//template <class T>
//T CyclicLinkedList<T>::back() const
//{
//    return List<T>::GetTail()->GetData();
//}

// Returns the number of nodes with the corresponding data in the list
template <class T>
int CyclicLinkedList<T>::count(T const &val) const
{
    if (List<T>::GetSize() == 0)
    {
        std::cout << "The list is empty" << std::endl;
        return 0;
    }

    Node<T> *node = List<T>::GetHead();
    int count = 0;

    do
    {
        if(node->GetData() == val) // check for node to count
            count++;

        node = node->GetNext();

    } while (node != List<T>::GetHead());

    return count;
}


// Pushes a new node onto the front of the list
template <class T>
void CyclicLinkedList<T>::push_front( T const &val)
{
    SingleNode<T> *node = new SingleNode<T>(val, NULL);

    // if list is empty
    if (List<T>::GetHead() == NULL)
    {
        List<T>::SetHead(node);
        List<T>::SetTail(node);
        node->SetNext(node);
        List<T>::SetSize(List<T>::GetSize() + 1);
    }
    else
    {   //first points to the head node
        Node<T> *first = List<T>::GetHead();
        node->SetNext(first);

        //updates Cyclic list info
        List<T>::SetHead(node);
        List<T>::SetSize(List<T>::GetSize() + 1);

        //the tail node next is now the new node
        List<T>::GetTail()->SetNext(List<T>::GetHead());
    }
}


// Pushes a new node onto the back of the list
template <class T>
void CyclicLinkedList<T>::push_back(T const &val)
{
    SingleNode<T> *node = new SingleNode<T>(val, NULL);

    //if list is empty
    if (List<T>::GetHead() == NULL)
    {
        //updates Cyclic list info
        List<T>::SetHead(node);
        List<T>::SetTail(node);
        List<T>::SetSize(List<T>::GetSize() + 1);
    }
    else
    {   //last points to the tail node
        Node<T> *last = List<T>::GetTail();
        last->SetNext(node);

        //updates Cyclic list info
        List<T>::SetTail(node);
        List<T>::SetSize(List<T>::GetSize() + 1);

        //the new node next is now the head
        node->SetNext(List<T>::GetHead());
    }
}


// Removes the node at the front of the list
template <class T>
T CyclicLinkedList<T>::pop_front()
{
    if (List<T>::empty())
    {
        std::cout << "The list is empty" << std::endl;
        return 0;
    }

    T popped = List<T>::front();

    if(List<T>::GetSize() == 1)
    {
        delete List<T>::GetHead();
        List<T>::SetSize(0);
        return 0;
    }

    Node<T> *first = List<T>::GetHead()->GetNext();

    //updates Cyclic list info
    List<T>::GetTail()->SetNext(first);
    List<T>::SetSize(List<T>::GetSize() - 1);


    //tail next is now the second element
    delete List<T>::GetHead();
    List<T>::SetHead(first);
    return popped;
}


// Removes the node at the front of the list
template <class T>
T CyclicLinkedList<T>::pop_back()
{
    if (List<T>::empty())
    {
        std::cout << "The list is empty" << std::endl;
        return 0;
    }

    T popped = List<T>::back();

    if(List<T>::GetSize() == 1)
    {
        delete List<T>::GetTail();
        List<T>::SetSize(0);
        return popped;
    }

    Node<T> *first = List<T>::GetHead(), *last = first->GetNext();

    // retrieve node before tail
    while (last->GetNext() != List<T>::GetTail())
        last = last->GetNext();

    delete List<T>::GetTail();
    List<T>::SetTail(last);
    List<T>::SetSize(List<T>::GetSize() - 1);

    //tail next is now the second element
    last->SetNext(List<T>::GetHead());

    return popped;
}

// function erases every element of the list with corresponding value
template <class T>
int CyclicLinkedList<T>::erase(T const &val)
{
    int count = 0;
    for(int i = 0; i <= List<T>::GetSize() - 1; i++)
    {
        count += (pop(val));
    }
    return count;
}

// Deletes nodes from the list sequentially
template <class T>
int CyclicLinkedList<T>::pop(const T &val)
{
    if (List<T>::GetHead()->GetData() == val) // If the value to delete is in the header
    {
        pop_front();
        return 1;
    }
    if (List<T>::GetSize() > 2) // Check through the middle of the list
    {
        Node<T> *current = List<T>::GetHead()->GetNext(), *prev = List<T>::GetHead();
        while(current != List<T>::GetTail())
        {
            if(current->GetData() == val) // If the value to delete is in the middle
            {
                prev->SetNext(current->GetNext());
                delete current;
                List<T>::SetSize(List<T>::GetSize() - 1);
                return 1;
            }
            prev = current;
            current = current->GetNext();
        }
    }
    if (List<T>::GetTail()->GetData() == val) // If the value to delete is in the tail
    {
        pop_back();
        return 1;
    }
    return 0;
}

// Prints the data in each node of the list
template <class T>
void CyclicLinkedList<T>::printList()
{
    if (List<T>::GetSize() == 0)
    {
        std::cout << "The list is empty" << std::endl;
    }
    else
    {
        std::cout << "List nodes:" << std::endl;
        Node<T> *node = List<T>::GetHead();
        do
        {
            node->Print();
            node = node->next;
        } while (node != List<T>::GetHead());
        std::cout << std::endl << "Size of list = " << List<T>::GetSize() << std::endl;
}
}

#endif