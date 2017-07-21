#ifndef LINKEDTREE_H
#define LINKEDTREE_H
#include "treeNode.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include <iomanip>

using namespace std;

template <class T>
class linkedTree {
private:
    treeNode<T> *root;
    int size;
    
public:
    linkedTree();
    linkedTree(const linkedTree& orig);
    virtual ~linkedTree();
   
    void SetRoot(treeNode<T> *);
    treeNode<T>* GetRoot()const;
    
    void SetSize(int count);
    int GetSize()const;
    
    int GetHeight();
    int GetHeight(treeNode<T> *)const;
    bool empty();
    
    int leaves();
    int leavesRecursive(treeNode<T> *);
    
    int siblings(treeNode<T> *);
    treeNode<T> * findNode(T);
    
    void preorder();
    void preorderRecursive(treeNode<T> *);
    
    void postorder();
    void postorderRecursive(treeNode<T> *);
    
    void inorder();
    void inorderRecursive(treeNode<T> *);
    
    void clear();
    void clearRecursive(treeNode<T> *);
    
    void del(T);
    void deleteRootNode(treeNode<T> *);
    void deleteChildNode(treeNode<T> *);
    treeNode<T> * findMinimunLeftChild(treeNode<T> *);
    void insert(T);
    
};

template <class T>
linkedTree<T>::linkedTree(){
    SetRoot(NULL);
    SetSize(0);
}

template <class T>
linkedTree<T>::~linkedTree(){
    std::cout << "~LinkedTree()" << std::endl;
    clear();
    delete root;
}

template <class T>
void linkedTree<T>::SetRoot(treeNode<T>* root) {
    this->root = root;
}
template <class T>
treeNode<T>* linkedTree<T>::GetRoot() const{
    return root;
}

template <class T>
void linkedTree<T>::SetSize(int size) {
    this->size = size;
}
template <class T>
int linkedTree<T>::GetSize()const{
    return size;
}

template <class T>
int linkedTree<T>::GetHeight(){
    treeNode<T> *ptr_root = this->GetRoot();
    if(ptr_root != NULL)
        return GetHeight(ptr_root);
    else
        return 0;
}
template <class T>
int linkedTree<T>::GetHeight(treeNode<T> *tree)const{
    int height_r, height_l;
    if(tree == NULL)
        return -1;
    treeNode<T> *ptr_right = tree->GetRight();
    treeNode<T> *ptr_left  = tree->GetLeft();
    if(ptr_right != 0){
        height_r = GetHeight(ptr_right) + 1;
    }else 
        height_r = 0;
    if(ptr_left != 0){
        height_l = GetHeight(ptr_left)+ 1;
    }else
        height_l=0;
    if(height_r > height_l)
        return height_r;
    else 
        return height_l;
}

template <class T>
bool linkedTree<T>::empty(){
    return (GetSize() == 0);
}

template <class T>
int linkedTree<T>::leaves(){
    treeNode<T> *ptr_root = GetRoot();
    if(ptr_root != 0)
        return leavesRecursive(ptr_root);
    else
        return 0;
}
template <class T>
int linkedTree<T>::leavesRecursive(treeNode<T> *tree){
    treeNode<T> *ptr_right, *ptr_left;
    int leave_count=0;
    ptr_right=tree->GetRight();
    ptr_left=tree->GetLeft();
    if(ptr_left == NULL && ptr_right ==NULL)
        return 1;
    if(ptr_left != NULL)
        leave_count = leave_count + leavesRecursive(ptr_left);
    if(ptr_right != NULL)
        leave_count = leave_count + leavesRecursive(ptr_right);
    return leave_count;
}

template <class T>
int linkedTree<T>::siblings(treeNode<T> *child){
    if(child != NULL){
        treeNode<T> *ptr_parent = child->GetParent();
        if(ptr_parent->GetRight() == NULL || ptr_parent->GetLeft() == NULL)
            return 0;
        else
            return 1;
    }else
        std::cout << "Node does not exist" << endl;
    return 0;
}

template <class T>
treeNode<T> * linkedTree<T>::findNode(T data){
    int found=0;
    T aux_data;
    treeNode<T> *ptr_search = GetRoot();
    if(empty()){
        std::cout << "Empty Tree" << endl;
        return NULL;
    }else{                                              //if more than 1 element
        while(!found && (ptr_search!=NULL)){            //insert as a leaf
            if((aux_data=ptr_search->GetValue()) == data){
                found = 1;                              //if data already exists
                break;                                  //break while()
            }
            if(data > aux_data)                         //if data > node->data
                ptr_search = ptr_search->GetRight();    //insert in right tree 
            else                                        
                ptr_search = ptr_search->GetLeft();     //insert in left tree
        }
        if(!found){
            std::cout << "Element not in the Tree" << endl;
            return NULL;
        }else
            return ptr_search;
    }
}

template <class T>
void linkedTree<T>::preorder(){
    std::cout << left <<setw(20)<< "Preorder: ";
    treeNode<T> *ptr_root = GetRoot();
    preorderRecursive(ptr_root);
    std::cout << endl;
}
template <class T>
void linkedTree<T>::preorderRecursive(treeNode<T> *tree){
    if(tree != NULL){
        std::cout << setw(3) <<tree->GetValue();// << std::endl;
        preorderRecursive(tree->GetLeft());
        preorderRecursive(tree->GetRight());
        delete tree;
        tree=NULL;
    }
}

template <class T>
void linkedTree<T>::postorder(){
    std::cout << left<<setw(20)<< "Postorder: ";
    treeNode<T> *ptr_root = GetRoot();
    postorderRecursive(ptr_root);
    std::cout << endl;
}
template <class T>
void linkedTree<T>::postorderRecursive(treeNode<T> *tree){
    if(tree != NULL){
        postorderRecursive(tree->GetLeft());
        postorderRecursive(tree->GetRight());
        std::cout << setw(3) <<tree->GetValue();// << std::endl;
    }
}

template <class T>
void linkedTree<T>::inorder(){
    std::cout << left<<setw(20)<< "Inorder: ";
    treeNode<T> *ptr_root = GetRoot();
    inorderRecursive(ptr_root);
    std::cout << endl;
}
template <class T>
void linkedTree<T>::inorderRecursive(treeNode<T> *tree){
    if(tree != NULL){
        inorderRecursive(tree->GetLeft());
        std::cout << setw(3) <<tree->GetValue();// << std::endl;
        inorderRecursive(tree->GetRight());
    }
}

template <class T>
void linkedTree<T>::clear(){
    clearRecursive(GetRoot());
    SetRoot(0);
    SetSize(0);
}

template <class T>
void linkedTree<T>::clearRecursive(treeNode<T> *tree){
    if(tree!= NULL){
        clearRecursive(tree->GetLeft());
        clearRecursive(tree->GetRight());
        std::cout << "Deleting : " << tree->GetValue() << endl;
        delete tree;
        tree=NULL;
    }
}

template <class T>
void linkedTree<T>::insert(T data){
    std::cout <<"Inserting : " <<data <<std::endl;
    int found =0;
    treeNode<T> *ptr_search = GetRoot(),*ptr_parent;
    T aux_data;
    if(ptr_search == NULL){                             //if tree is empty
        treeNode<T> *new_node = new treeNode<T>(data);
        SetRoot(new_node);                              //update root*
        SetSize(GetSize()+1);                           //increase size by 1
    }else{                                              //if more than 1 element
        while(!found && (ptr_search!=NULL)){            //insert as a leaf
            if((aux_data = ptr_search->GetValue()) == data){
                found = 1;                              //if data already exists
                break;                                  //break while()
            }
            ptr_parent = ptr_search;
            if(data > aux_data)                         //if data > node->data
                ptr_search = ptr_search->GetRight();    //insert in right tree 
            else                                        
                ptr_search = ptr_search->GetLeft();     //insert in left tree
        }
        if(!found){                                     //if data was not located
            treeNode<T> *new_node = new treeNode<T>(data);
            new_node->SetParent(ptr_parent);            //update parent*
            if(data > ptr_parent->GetValue())            //if data>parent->data
                ptr_parent->SetRight(new_node);         //update right*
            else
                ptr_parent->SetLeft(new_node);          //update left*
            SetSize(GetSize()+1);                       //update size
        }else
            std::cout << "Element already in the Tree" << std::endl;
    }
}

//template <class T>
//void linkedTree<T>::del(T d){
//    int found = 0;
//    treeNode<T> *ptr_parent,*ptr_del = this->findNode(d),*ptr_suc,*subTree;
//    if(ptr_del != NULL){
//        ptr_parent = ptr_del->GetParent();
//        found = 1;
//    }
//    if(found){
//        if(ptr_del->GetRight() != NULL && ptr_del->GetLeft() != NULL){
//            ptr_suc = ptr_del->GetRight();
//            ptr_parent = ptr_del;
//            while(ptr_suc->GetLeft() != NULL){
//                ptr_parent = ptr_suc;
//                ptr_suc = ptr_suc->GetLeft();
//            }
//            ptr_del->SetValue(ptr_suc->GetValue());
//            ptr_del = ptr_suc;
//        }
//        subTree = ptr_del->GetLeft();
//        if(subTree == NULL)
//            subTree = ptr_del->GetRight();
//        if(ptr_parent == NULL)
//            SetRoot(subTree);
//        else if(ptr_parent->GetLeft() == ptr_del)
//            ptr_parent->SetLeft(subTree);
//        else
//            ptr_parent->SetRight(subTree);
//        delete ptr_del;
//    }
//    else
//        std:cout << "Element not found: " << d << std::endl;
//}
template <class T>
void linkedTree<T>::del(T d){
    std::cout << "LinkedTree delete()" << std::endl;
    treeNode<T> *ptr_del = findNode(d);        //find node to be deleted
    if(ptr_del != 0 && ptr_del==GetRoot())     //d is in root node
        deleteRootNode(ptr_del);
    else if(ptr_del != 0)                      //d is in a child node
        deleteChildNode(ptr_del);
    else                                       //d is not in the tree
        std::cout << "Element not in the Tree" << std::endl;
}

template <class T>
void linkedTree<T>::deleteRootNode(treeNode<T> *ptr_del){
    if(ptr_del->GetRight()== NULL && ptr_del->GetLeft() == NULL){// root is a leaf node
        SetRoot(NULL);
        delete ptr_del;
    }else{                                                           //root is not a leaf node
        treeNode<T> *min_max = findMinimunLeftChild(ptr_del->GetRight());
        if(min_max == NULL){                                         //root has no right child
            treeNode<T> *aux = ptr_del;
            ptr_del->GetLeft()->SetParent(NULL);
            SetRoot(ptr_del->GetLeft());
            delete aux;
        }else{                                                       //root has right child, min_max is either leaf node or not
            if(min_max->GetParent() != ptr_del){                                                   //min_max is a left child of a tree
                min_max->GetParent()->SetLeft(min_max->GetRight());      //min_max parent points to min_max right child
                if(min_max->GetRight()!=NULL)
                    min_max->GetRight()->SetParent(min_max->GetParent());    //min_max right child becomes child of min_max parent
            }else
                ptr_del->SetRight(min_max->GetRight());
            ptr_del->SetValue(min_max->GetValue());
        }
        delete min_max;                                                  //delete the root node
    }
    SetSize(GetSize()-1);                                                  //size reduced by 1
}

template <class T>
void linkedTree<T>::deleteChildNode(treeNode<T> *ptr_del){
    if(ptr_del->GetLeft()==NULL && ptr_del->GetRight()==NULL){  //ptr_del is a leaf node
        if(ptr_del->GetParent()->GetLeft() == ptr_del)
            ptr_del->GetParent()->SetLeft(NULL);
        else
            ptr_del->GetParent()->SetRight(NULL);
        delete ptr_del;
    }else{                                                      //ptr_del not a leaf node
        treeNode<T> *min_max = this->findMinimunLeftChild(ptr_del->GetRight());
        if(min_max == NULL){                                    //ptr_del has no right child
            if(ptr_del->GetParent()->GetLeft() == ptr_del){   //ptr_del is a left child
                ptr_del->GetParent()->SetLeft(ptr_del->GetLeft());
                ptr_del->GetLeft()->SetParent(ptr_del->GetParent());
            }else{                                            //ptr_del is a right child
                ptr_del->GetParent()->SetRight(ptr_del->GetRight());
                ptr_del->GetRight()->SetParent(ptr_del->GetParent());
            }
            delete ptr_del;
        }else{                                                  //ptr_del has right child,min+max is either a leaf node or not
            if(min_max->GetParent() != ptr_del){                //ptr_del right child is min_max                                                   //min_max is a left child of a tree
                min_max->GetParent()->SetLeft(min_max->GetRight());      //min_max parent points to min_max right child
                if(min_max->GetRight()!=NULL)
                    min_max->GetRight()->SetParent(min_max->GetParent());    //min_max right child becomes child of min_max parent
            }else{
                ptr_del->SetRight(min_max->GetRight());
                if(min_max->GetRight() != NULL)
                    min_max->GetRight()->SetParent(ptr_del);
                ptr_del->SetValue(min_max->GetValue());
            }
            delete min_max;
        }
    }
    SetSize(GetSize()-1);
}

template <class T>
treeNode<T> * linkedTree<T>::findMinimunLeftChild(treeNode<T> *subtree){
    if(subtree == 0)
        return subtree;
    else{
        if(subtree->GetLeft() == NULL)
            return subtree;
        else
            return findMinimunLeftChild(subtree->GetLeft());
    }
}
#endif /* GENERALTREE_H */

