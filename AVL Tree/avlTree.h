#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

#include "linkedTree.h"
#include "treeNode.h"

using namespace std;

template <class T>
class avlTree : public linkedTree<T>{
public:
    avlTree();
    avlTree(const avlTree& orig);
    virtual ~avlTree();
     
    
    
    void insert(T);
    treeNode<T> * insertRecursive(treeNode<T> *, T);
    void del(T);
    void deleteRootNode(treeNode<T> *);
    void deleteChildNode(treeNode<T> *);
    
    void balanceTree(treeNode<T> *);
    void balanceTreeDeletion(treeNode<T> *, int);
    
    void singleRotationFromRight(treeNode<T> *);
    void singleRotationFromLeft(treeNode<T> *);
    
    void doubleRotationFromRight(treeNode<T> *);
    void doubleRotationFromLeft(treeNode<T> *);
    void calculateBalanceFactor(treeNode<T> *,treeNode<T> *);
};

template <class T>
avlTree<T>::avlTree():linkedTree<T>(){
    
}
template <class T>
avlTree<T>::~avlTree(){
}

template <class T>
void avlTree<T>::insert(T d){
    std::cout << "AvlTree insert() : Element = " << d<< std::endl;
    treeNode<T> *ptr_node = linkedTree<T>::GetRoot();
    if(ptr_node == NULL){
        treeNode<T> *new_node = new treeNode<T>(d);
        linkedTree<T>::SetRoot(new_node);
        linkedTree<T>::SetSize(linkedTree<T>::GetSize()+1);
    }else{
        treeNode<T> *ptr_search;
        ptr_search = insertRecursive(ptr_node,d);
        if(ptr_search == NULL){
            std::cout << "Element already in the tree" << std::endl;
        }else{
            treeNode<T> *new_node = new treeNode<T>();
            new_node->SetValue(d);
            new_node->SetParent(ptr_search);
            if(ptr_search->GetValue() > d)
                ptr_search->SetLeft(new_node);
            else
                ptr_search->SetRight(new_node);
            linkedTree<T>::SetSize(linkedTree<T>::GetSize()+1);
            balanceTree(new_node);
        }
    }
}
template <class T>
treeNode<T> * avlTree<T>::insertRecursive(treeNode<T> *ptr_search,T d){
    if(ptr_search->GetValue() == d)
        return NULL;
    if(ptr_search->GetValue() > d ){
        if (ptr_search->GetLeft() != NULL)
            return insertRecursive(ptr_search->GetLeft(), d);
        else
            return ptr_search;
    }else{
        if(ptr_search->GetRight() != NULL)
            return insertRecursive(ptr_search->GetRight(), d);
        else
            return ptr_search;
    }
}

template <class T>
void avlTree<T>::del(T d){
    std::cout << "Avl delete(): " << d << std::endl;
    treeNode<T> *ptr_del = linkedTree<T>::findNode(d);        //find node to be deleted
    if(ptr_del != 0 && ptr_del==linkedTree<T>::GetRoot())     //d is in root node
        deleteRootNode(ptr_del);
    else if(ptr_del != 0)                      //d is in a child node
        deleteChildNode(ptr_del);
    else                                       //d is not in the tree
        std::cout << "Element not in the Tree" << std::endl;
}

template <class T>
void avlTree<T>::deleteRootNode(treeNode<T> *ptr_del){
    int i=1; //right=1 , left=-1
    if(ptr_del->GetRight()== NULL && ptr_del->GetLeft() == NULL){// root is a leaf node
        linkedTree<T>::SetRoot(NULL);
        delete ptr_del;
    }else{                                                           //root is not a leaf node
        treeNode<T> *min_max = linkedTree<T>::findMinimunLeftChild(ptr_del->GetRight());
        if(min_max == NULL){                                         //root has no right child
            treeNode<T> *aux = ptr_del;
            ptr_del->GetLeft()->SetParent(NULL);
            linkedTree<T>::SetRoot(ptr_del->GetLeft());
            delete aux;
        }else{                                                       //root has right child, min_max is either leaf node or not
            if(min_max->GetParent() != ptr_del){                                                   //min_max is a left child of a tree
                min_max->GetParent()->SetLeft(min_max->GetRight());
                i=-1;
            }      //min_max parent points to min_max right child
            else
                ptr_del->SetRight(min_max->GetRight());
            if(min_max->GetRight()!=NULL)
                    min_max->GetRight()->SetParent(min_max->GetParent());    //min_max right child becomes child of min_max parent
            ptr_del->SetValue(min_max->GetValue());
            balanceTreeDeletion(min_max,i);
            delete min_max;
        }                                                  //delete the root node
    }
    linkedTree<T>::SetSize(linkedTree<T>::GetSize()-1);                                                  //size reduced by 1
}

template <class T>
void avlTree<T>::deleteChildNode(treeNode<T> *ptr_del){
    int i=1;   //right = 1 , left =-1;
    if(ptr_del->GetLeft()==NULL && ptr_del->GetRight()==NULL){  //ptr_del is a leaf node
        if(ptr_del->GetParent()->GetLeft() == ptr_del){
            ptr_del->GetParent()->SetLeft(NULL);
            i=-1;
        }else
            ptr_del->GetParent()->SetRight(NULL);
        balanceTreeDeletion(ptr_del,i);
        delete ptr_del;
    }else{                                                      //ptr_del not a leaf node
        treeNode<T> *min_max = linkedTree<T>::findMinimunLeftChild(ptr_del->GetRight());
        if(min_max == NULL){                                    //ptr_del has no right child
            if(ptr_del->GetParent()->GetLeft() == ptr_del){   //ptr_del is a left child
                ptr_del->GetParent()->SetLeft(ptr_del->GetLeft());
                ptr_del->GetLeft()->SetParent(ptr_del->GetParent());
                i=-1;
            }else{                                            //ptr_del is a right child
                ptr_del->GetParent()->SetRight(ptr_del->GetLeft());
                ptr_del->GetLeft()->SetParent(ptr_del->GetParent());
            }
            balanceTreeDeletion(ptr_del, i);
            delete ptr_del;
        }else{            
            if(min_max->GetParent() != ptr_del){                //ptr_del right child is min_max                                                   //min_max is a left child of a tree
                min_max->GetParent()->SetLeft(min_max->GetRight());      //min_max parent points to min_max right child
                if(min_max->GetRight()!=NULL)
                    min_max->GetRight()->SetParent(min_max->GetParent());    //min_max right child becomes child of min_max parent
                i=-1;
            }else{
                ptr_del->SetRight(min_max->GetRight());
                if(min_max->GetRight() != NULL)
                    min_max->GetRight()->SetParent(ptr_del);
                ptr_del->SetValue(min_max->GetValue());
            }
            balanceTreeDeletion(min_max,i);//ptr_del has right child,min+max is either a leaf node or not
            delete min_max;
        }
    }
    linkedTree<T>::SetSize(linkedTree<T>::GetSize()-1);
}

template <class T>
void avlTree<T>::balanceTree(treeNode<T> *node){
    treeNode<T> *ptr_child = node;
    treeNode<T> *ptr_parent = node->GetParent();
    int balFact;
    while(ptr_parent != NULL){
        if(ptr_parent->GetRight() == ptr_child)           //calculate parent's balance factor
            balFact= ptr_parent->GetBalanceFactor()-1;
        else
            balFact= ptr_parent->GetBalanceFactor()+1;
        if(balFact == 0){                                 //if leveled, do nothing
            ptr_parent->SetBalanceFactor(balFact);
            break;
        }
        if(balFact == -2){                                // double right-high
            if(ptr_child->GetBalanceFactor() == -1){      //same direction
                singleRotationFromRight(ptr_parent);
                //calculateBalanceFactor(ptr_parent, ptr_parent->GetParent()->GetRight());
                ptr_parent->SetBalanceFactor(0);
                ptr_parent->GetParent()->SetBalanceFactor(0);
            }
            else
                doubleRotationFromRight(ptr_parent);    //opposite direction
            break;
        }
        if(balFact == 2){                               // double left-high
            if(ptr_child->GetBalanceFactor() == 1){      // same direction
                singleRotationFromLeft(ptr_parent);
                //calculateBalanceFactor(ptr_parent, ptr_parent->GetParent()->GetLeft());
                ptr_parent->SetBalanceFactor(0);
                ptr_parent->GetParent()->SetBalanceFactor(0);
            }
            else
                doubleRotationFromLeft(ptr_parent);     //opposite direction
            break;
        }
        ptr_parent->SetBalanceFactor(balFact);          //parent new bfactor -1 or 1
        ptr_child = ptr_parent;
        ptr_parent = ptr_parent->GetParent();
    }
}

template <class T>
void avlTree<T>::balanceTreeDeletion(treeNode<T> * node, int i){ //min_max
    int balFact;
    treeNode<T> * ptr_child = node;
    treeNode<T> * ptr_parent = node->GetParent();
    while(ptr_parent != NULL){
        balFact= ptr_parent->GetBalanceFactor() + i;
        ptr_parent->SetBalanceFactor(balFact);
        if(balFact == 1 || balFact == -1)
            break;
        if(balFact == -2){                                // double right-high
            if(ptr_parent->GetRight()->GetBalanceFactor() == -1 || ptr_parent->GetRight()->GetBalanceFactor() == 0){      //same direction
                singleRotationFromRight(ptr_parent);                
                ptr_parent->SetBalanceFactor(0);
                ptr_parent->GetParent()->SetBalanceFactor(0);
                //ptr_parent->SetLeft(NULL);
            }else{
                doubleRotationFromRight(ptr_parent);    //opposite direction
            }
        }
        if(balFact == 2){                               // double left-high
            if(ptr_parent->GetLeft()->GetBalanceFactor() == 1 || ptr_parent->GetLeft()->GetBalanceFactor() == 0){      // same direction
                singleRotationFromLeft(ptr_parent);
                ptr_parent->SetBalanceFactor(0);
                ptr_parent->GetRight()->SetBalanceFactor(0);
            }else
                    doubleRotationFromLeft(ptr_parent);     //opposite direction
        }
        ptr_child = ptr_parent;
        ptr_parent = ptr_parent->GetParent();
        if(ptr_parent != NULL && ptr_parent->GetLeft() == ptr_child)
            i = -1;
        else
            i = 1;
    }
}
template <class T>
void avlTree<T>::singleRotationFromRight(treeNode<T> *ptr_parent){
    std::cout << "Single Rotation from Right: " << ptr_parent->GetValue() << std::endl;
    treeNode<T> *ptr_child = ptr_parent->GetRight();
    treeNode<T> * ptr_great_parent = ptr_parent->GetParent();
    ptr_parent->SetRight(ptr_child->GetLeft()); 
    if(ptr_child->GetLeft() != NULL)
        ptr_child->GetLeft()->SetParent(ptr_parent);
    ptr_child->SetLeft(ptr_parent);
    ptr_parent->SetParent(ptr_child);
    ptr_child->SetParent(ptr_great_parent);
    if(ptr_great_parent == NULL)
        linkedTree<T>::SetRoot(ptr_child);
    else if(ptr_great_parent->GetLeft() == ptr_parent)
        ptr_great_parent->SetLeft(ptr_child);
    else
        ptr_great_parent->SetRight(ptr_child);
}
template <class T>
void avlTree<T>::singleRotationFromLeft(treeNode<T> *ptr_parent){
    std::cout << "Single Rotation from Left: " << ptr_parent->GetValue() << std::endl;
    treeNode<T> *ptr_child = ptr_parent->GetLeft();
    treeNode<T> * ptr_great_parent = ptr_parent->GetParent();
    ptr_parent->SetLeft(ptr_child->GetRight());
    if(ptr_child->GetRight() != NULL)    
        ptr_child->GetRight()->SetParent(ptr_parent);
    ptr_child->SetRight(ptr_parent);
    ptr_parent->SetParent(ptr_child);
    ptr_child->SetParent(ptr_great_parent);
    if(ptr_great_parent == NULL)
        linkedTree<T>::SetRoot(ptr_child);
    else if(ptr_great_parent->GetLeft() == ptr_parent)
        ptr_great_parent->SetLeft(ptr_child);
    else
        ptr_great_parent->SetRight(ptr_child);
}
template <class T>

void avlTree<T>::doubleRotationFromRight(treeNode<T> *ptr_parent){
    std::cout << "Double rotation From right over : " << ptr_parent->GetValue() << endl;
    ptr_parent->GetRight()->GetLeft()->SetBalanceFactor(0);
    singleRotationFromLeft(ptr_parent->GetRight());
    singleRotationFromRight(ptr_parent);
    calculateBalanceFactor(ptr_parent, ptr_parent->GetParent()->GetRight());
}
template <class T>
void avlTree<T>::doubleRotationFromLeft(treeNode<T> *ptr_parent){
    std::cout << "Double rotation From left over : " << ptr_parent->GetValue() << endl;
    ptr_parent->GetLeft()->GetRight()->SetBalanceFactor(0);
    singleRotationFromRight(ptr_parent->GetLeft());
    singleRotationFromLeft(ptr_parent);
    calculateBalanceFactor(ptr_parent, ptr_parent->GetParent()->GetLeft());
}

template <class T>
void avlTree<T>::calculateBalanceFactor(treeNode<T> *tree_A,treeNode<T> *tree_B){
    int height_right_A,height_left_A,height_right_B,height_left_B;
    height_right_A = linkedTree<T>::GetHeight(tree_A->GetRight());
    height_left_A  = linkedTree<T>::GetHeight(tree_A->GetLeft());
    if(height_right_A == height_left_A)
        tree_A->SetBalanceFactor(0);
    else if(height_right_A > height_left_A)
        tree_A->SetBalanceFactor(-1);
    else
        tree_A->SetBalanceFactor(1);
    
    height_right_B = linkedTree<T>::GetHeight(tree_B->GetRight())+1;
    height_left_B  = linkedTree<T>::GetHeight(tree_B->GetLeft())+1;
    if(height_right_B == height_left_B)
        tree_B->SetBalanceFactor(0);
    else if(height_right_B > height_left_B)
        tree_B->SetBalanceFactor(-1);
    else
        tree_B->SetBalanceFactor(1);
}
#endif /* AVLTREE_H */

