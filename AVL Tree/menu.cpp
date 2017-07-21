#include <cstdlib>
#include <iostream>

#include "linkedTree.h"
#include "treeNode.h"
#include "avlTree.h"

using namespace std;

typedef string Type;
void testLinkedTree();
void testAvlTree();
void leftHighTree(avlTree<Type> *);
void rightHighTree(avlTree<Type> *);
void testMaxHeap();

int main(int argc, char** argv) {
    //testLinkedTree();
    testAvlTree();
    //testMaxHeap();
    return 0;
}

void testLinkedTree(){
    linkedTree<Type> *tree = new linkedTree<Type>();
    std::cout << tree->GetSize() << std::endl;
    tree->insert("gsfg");
    std::cout << "Deleting 45:" << std::endl;
    tree->del("gsfg");
    tree->postorder();
    tree->insert("dsfg");
    tree->insert("wdfs");
    std::cout << "Deleting 50:" << std::endl;
    tree->del("wdfs");
    tree->postorder();
    tree->insert("25");
    tree->insert("15");
    tree->insert("33");
    tree->insert("75");
    std::cout << "Deleting 35:" << std::endl;
    tree->del("shsg");
    tree->postorder();
    tree->insert("sggs");
    tree->insert("sgsg");
//    tree->insert("sgjg");
//    tree->insert("sgj,k");
//    tree->insert("pijp");
//    tree->insert("ppun");
//    tree->insert("nvbs");
//    tree->insert("sgjsg");
//    tree->insert("sjsg");
    tree->insert("jkgf");
    tree->insert("dhgs");
    std::cout << tree->GetSize() << std::endl;
    tree->preorder();
    tree->postorder();
    tree->inorder();
//    std:cout << "# of Leaves: " << tree->leaves() << std::endl;
    treeNode<Type> *node = tree->findNode("2");
//    if(node!=NULL){
//        std::cout << "Node element: " << node->GetValue() << std::endl;
//        std::cout << "Tree Height: " << tree->GetHeight(node) <<std::endl;
//        std::cout << "#Siblings: " << tree->siblings(node) << std::endl;
//    }
    node = tree->findNode("7");
    if(node!=NULL){
        std::cout << "Node element: " << node->GetValue() << std::endl;
        std::cout << "Tree Height: " << tree->GetHeight(node) <<std::endl;
        std::cout << "#Siblings: " << tree->siblings(node) << std::endl;
    }
    node = tree->findNode("10");
    if(node!=NULL)
        std::cout << "Node element: " << node->GetValue() << std::endl;

    std::cout << "Tree Height: " << tree->GetHeight() <<std::endl;
    
    std::cout << "Deleting 45:" << std::endl;
    tree->del("45");
    tree->postorder();
    std::cout << "Deleting 35:" << std::endl;
    tree->del("35");
    tree->postorder();
    std::cout << "Deleting 25:" << std::endl;
    tree->del("25");
    tree->postorder();
    std::cout << "Deleting 50:" << std::endl;
    tree->del("50");
    tree->postorder();
    std::cout << "Deleting 75:" << std::endl;
    tree->del("75");
    tree->postorder();
    tree->del("120");
    tree->postorder();
    tree->del("110");
    tree->postorder();
    tree->postorder();
    std::cout<< "Tree size: " <<tree->GetSize() << std::endl;
    tree->clear();
    treeNode<Type> * root = tree->GetRoot();
    if(root!=NULL)
        std::cout<< "Root: " <<tree->GetRoot()->GetValue() << std::endl;
    tree->clear();
    tree->clear();
    delete tree;
    if(root!=NULL)
        std::cout<< "Root: " <<tree->GetRoot()->GetValue() << std::endl;
}

void testAvlTree(){
    avlTree<Type> *tree= new avlTree<Type>();
    tree->insert("45");
    std::cout << "Deleting 45:" << std::endl;
    tree->del("45");
    tree->postorder();
    tree->insert("50");
    tree->insert("35");
    std::cout << "Deleting 50:" << std::endl;
    tree->del("50");
    tree->postorder();
    avlTree<Type> *tree_l=new avlTree<Type>();
    leftHighTree(tree_l);
    avlTree<Type> *tree_r=new avlTree<Type>();;
    rightHighTree(tree_r);
    std::cout << tree->GetSize() << std::endl;
    tree->insert("9");
    tree->postorder();
    tree->insert("6");
    tree->postorder();
    tree->insert("17");
    tree->postorder();
    tree->insert("4");
    tree->insert("5");
    tree->insert("54");
    tree->insert("48");
    
    tree->postorder();
    tree->insert("1");
    tree->postorder();
    tree->insert("3");
    tree->postorder();
    tree->insert("5");
    tree->postorder();
    tree->insert("30");
    
//    std::cout << "Deleting 50:" << std::endl;
//    tree->del(50);
    tree->postorder();
    tree->insert("70");
    tree->postorder();
    tree->insert("0");
    tree->postorder();
    tree->del("30");
    tree->postorder();
    tree->del("17");
    tree->postorder();
//    std::cout << "Deleting 35:" << std::endl;
//    tree->del(35);
    tree->insert("4");
    tree->postorder();
    tree->insert("7");
    tree->postorder();
    tree->insert("3");
    tree->postorder();
    tree->insert("2");
    tree->postorder();
    tree->insert("16");
    tree->postorder();
    tree->insert("77");
    tree->postorder();
    tree->insert("32");
    tree->postorder();
    tree->insert("62");
    tree->postorder();
    tree->del(tree->GetRoot()->GetValue());
    tree->postorder();
    tree->insert("24");
    tree->postorder();
    tree->insert("74");
    tree->postorder();
    tree->del(tree->GetRoot()->GetValue());
    tree->postorder();
    tree->insert("35");
    tree->postorder();
    tree->insert("22");
    tree->postorder();
    tree->insert("15");
    tree->del(tree->GetRoot()->GetValue());
    tree->postorder();
    tree->postorder();
    tree->insert("23");
    tree->postorder();
    std::cout << tree->GetSize() << std::endl;
    tree->preorder();
    tree->postorder();
    tree->inorder();
    std:cout << "# of Leaves: " << tree->leaves() << std::endl;
    treeNode<Type> *node = tree->findNode("2");
    if(node!=NULL){
        std::cout << "Node element: " << node->GetValue() << std::endl;
        std::cout << "Tree Height: " << tree->GetHeight(node) <<std::endl;
        std::cout << "#Siblings: " << tree->siblings(node) << std::endl;
    }
    node = tree->findNode("7");
    if(node!=NULL){
        std::cout << "Node element: " << node->GetValue() << std::endl;
        std::cout << "Tree Height: " << tree->GetHeight(node) <<std::endl;
        std::cout << "#Siblings: " << tree->siblings(node) << std::endl;
    }
    node = tree->findNode("10");
    if(node!=NULL)
        std::cout << "Node element: " << node->GetValue() << std::endl;

    std::cout << "Tree Height: " << tree->GetHeight() <<std::endl;
    std::cout << "Deleting 5:" << std::endl;
    tree->del("5");
//    tree->postorder();
//    std::cout << "Deleting 1:" << std::endl;
//    tree->del("1");
//    tree->postorder();
//    std::cout << "Deleting 10:" << std::endl;
//    tree->del("10");
//    tree->postorder();
//    std::cout << "Deleting 17:" << std::endl;
//    tree->del("17");
//    tree->postorder();
//    std::cout << "Deleting 4:" << std::endl;
//    tree->del("4");
//    tree->postorder();
//    std::cout << "Deleting 15:" << std::endl;
//    tree->del("15");
//    tree->postorder();
    std::cout << "Deleting 20:" << std::endl;
    tree->del("20");
    tree->postorder();
    std::cout << "Deleting 78:" << std::endl;
    tree->del("78");
    tree->postorder();
    std::cout << "Deleting 48:" << std::endl;
    tree->del("48");
    tree->postorder();
    std::cout << "Deleting 62:" << std::endl;
    tree->del("62");
    std::cout << "Deleting 20:" << std::endl;
    tree->del("20");
    tree->postorder();
    std::cout << tree->GetSize() << std::endl;
    delete tree;
    delete tree_r;
    delete tree_l;
}

void testMaxHeap(){
//    treeNode<Type> *maxHeap = new treeNode<Type>[5];
//    treeNode<Type> node;
//    node.SetKey(100);
//    node.SetValue(59);
//    maxHeap[4]=node;
//    for(int i=0;i<5;i++){
//        std::cout << maxHeap[i].GetKey() << std::endl;
//        std::cout << maxHeap[i].GetValue() << std::endl;
//    }   
}

void leftHighTree(avlTree<Type> *tree){
    std::cout << "LEFT HIGH TREE:" << std::endl;
    tree->insert("20");
    tree->del("20");
    tree->postorder();
    tree->insert("20");
    tree->insert("15");
    tree->del("15");
    tree->postorder();
    tree->insert("30");
    tree->del("30");
    tree->postorder();
    tree->insert("10");
    tree->postorder();
    tree->insert("17");
    tree->postorder();
    //tree->del(30);    //works
    tree->insert("19");
    tree->del("10");
    tree->postorder();
    tree->insert("13");
    tree->postorder();
    tree->del("17");
    tree->postorder();
}

void rightHighTree(avlTree<Type> *tree){
    std::cout << "RIGHT HIGH TREE:" << std::endl;
    tree->insert("20");
    tree->postorder();
    tree->insert("15");
    tree->postorder();
    tree->insert("30");
    tree->postorder();
    tree->insert("25");
    tree->postorder();
    tree->insert("40");
    tree->postorder();
//    tree->del(15);// works
    tree->insert("23");
    tree->postorder();
    tree->insert("46");
    tree->postorder();
    tree->del("25");
    tree->postorder();
}