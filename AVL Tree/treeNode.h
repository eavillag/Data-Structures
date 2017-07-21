#ifndef TREENODE_H
#define TREENODE_H

#include <stdio.h>

template<class T>
class treeNode {
private: 
    T value;
    treeNode *right;
    treeNode *left;
    treeNode *parent;
    int balanceFactor;
    int key;
public:
    treeNode();
    treeNode(T &);
    treeNode(const treeNode& orig);
    ~treeNode();
    
    void SetValue(T value);
    T GetValue()const;
    
    void SetRight(treeNode*);
    treeNode* GetRight()const;
    
    void SetLeft(treeNode*);
    treeNode* GetLeft()const;
    
    void SetParent(treeNode*);
    treeNode* GetParent()const;
    
    void SetBalanceFactor(int balanceFactor);
    int GetBalanceFactor()const;
    
    void SetKey(int key);
    int GetKey()const;
};

template <class T>
treeNode<T>::treeNode(){
    //SetData();
    this->SetLeft(NULL);
    this->SetRight(NULL);
    this->SetParent(NULL);
    this->SetKey(0);
    this->SetBalanceFactor(0);
}

template <class T>
treeNode<T>::treeNode(T &d){
    SetValue(d);
    this->SetLeft(NULL);
    this->SetRight(NULL);
    this->SetParent(NULL);
    this->SetKey(0);
    this->SetBalanceFactor(0);
}

template <class T>
treeNode<T>::treeNode(const treeNode& orig){
}

template <class T>
treeNode<T>::~treeNode(){
}


template <class T>
void treeNode<T>::SetValue(T data) {
    this->value = data;
}
template <class T>
T treeNode<T>::GetValue() const{
    return value;
}

template <class T>
void treeNode<T>::SetRight(treeNode* right) {
    this->right = right;
}
template <class T>
treeNode<T>* treeNode<T>::GetRight() const{
    return right;
}

template <class T>
void treeNode<T>::SetLeft(treeNode* left) {
    this->left = left;
}
template <class T>
treeNode<T>* treeNode<T>::GetLeft() const{
    return left;
 }

template <class T>
void treeNode<T>::SetParent(treeNode* parent) {
    this->parent = parent;
}
template <class T>
treeNode<T>* treeNode<T>::GetParent()  const{
    return parent;
}

template <class T>
void treeNode<T>::SetBalanceFactor(int balanceFactor) {
    this->balanceFactor = balanceFactor;
}
template <class T>
int treeNode<T>::GetBalanceFactor() const{
    return balanceFactor;
}

template <class T>
void treeNode<T>::SetKey(int key) {
    this->key = key;
}
template <class T>
int treeNode<T>::GetKey() const{
    return key;
}
    

#endif /* TREENODE_H */

