#include <cstdlib>
#include <string>
#include <list>
#include <iostream>
#include "DirGraph.h"
#include "Graph.h"
#include "Edge.h"

typedef string Type;

using namespace std;
void showMenuGraph();
void showMenuDirGraph();
int executeActionDirGraph(int,DirGraph*&);
int executeActionGraph(int , Graph*&);

void testDirGraph();
int main(int argc, char** argv) {
    //testDirGraph();
    char c;
    int op,exit=0;
    cout << "Enter 'd' or 'u'" <<endl;
    cin >> c;
    if(c!= 'd' && c!= 'u')
        cout << "Wrong option" << endl;
    else{
        if(c == 'd')
        {
            DirGraph *dirGraph = new DirGraph();          // Allocate memory for new LinkedTree object
            showMenuDirGraph();
            cout << "Enter an option XXXXX" << endl;
            cin >> op;

            exit = executeActionDirGraph(op,dirGraph);
            while(!exit){                            // run through options until user terminates
                cout << "Enter an option: ";
                cin >> op;
                exit = executeActionDirGraph(op,dirGraph);
            }
        }
        else if(c == 'u')
        {
        Graph *graph = new Graph();          // Allocate memory for new MaxHeapTree object
            showMenuGraph();
            cout << "Enter an option" << endl;
            cin >> op;

            exit = executeActionGraph(op,graph);
            while(!exit){                            // run through options until user terminates
                cout << "Enter an option: ";
                cin >> op;
                exit = executeActionGraph(op,graph);
            }
        }
    }
    return 0;
}
// displays the menu options for a general/AVL tree to the user
void showMenuDirGraph(){
    cout << "1. Empty?" << endl;
    cout << "2. InDregree (v)" << endl;
    cout << "3. OutDegree (v)" << endl;
    cout << "4. Edge count" << endl;
    cout << "5. Adjacent (u,v)" << endl;
    cout << "6. DFS" << endl;
    cout << "7. BFS" << endl;
    cout << "8. Print Short path (v)" << endl;
    cout << "9. Clear" << endl;
    cout << "10. Insert (u,v,w)" << endl;
    cout << "11. Exit" << endl;
}

// displays the menu options for a heap to the user
void showMenuGraph(){
    cout << "1. Empty?" << endl;
    cout << "2. Dregree (v)" << endl;
    cout << "3. Edge count" << endl;
    cout << "4. isConnected?" << endl;
    cout << "5. Adjacent (u,v)" << endl;
    cout << "6. DFS" << endl;
    cout << "7. BFS" << endl;
    cout << "8. Print MST (v)" << endl;
    cout << "9. Clear" << endl;
    cout << "10. Insert (u,v,w)" << endl;
    cout << "11. Exit" << endl;

}

// executes the action on the General Tree that has been selected by the user
int executeActionDirGraph(int op, DirGraph *&dirGraph){
    int exit=0;
    string elem,e1,e2;
    list<Edge> *path; 
    list<Edge>::iterator it;
 //   treeNode<Type>* node;
    switch(op){
        case 1:
            if(!dirGraph->empty())
                cout << "Directed Graph is Empty" << endl;
            else
                cout  << "Directed Graph is NOT Empty"  << endl;
            break;
        case 2:
            cout << "Enter Vertex key: ";
            cin >> elem;
            cout  << "InDegree(): " << dirGraph->inDegree(elem) << endl;
            break;
        case 3:
            cout << "Enter Vertex key: ";
            cin >> elem;
            cout  << "OutDegree(): " << dirGraph->outDegree(elem) << endl;
            break;
        case 4:
            cout << "Edge Count :" << dirGraph->edgeCount() << endl;
            break;
        case 5:
            cout << "Enter vertex a and b";
            cin  >> e1 >> e2;
            if(dirGraph->adjacent(e1,e2)!=-1)
                cout << "Vertex are adjacent" << endl;
            else
                cout  << "Vertexes are not adjacent" << endl;
            break;
        case 6:
            cout << "Enter vertex: ";
            cin  >> e1;
            dirGraph->DFS(e1);
            break;
        case 7:
            cout << "Enter vertex: ";
            cin  >> e1;
            dirGraph->BFS(e1);
            break;
        case 8:
            cout << "Enter vertex: ";
            cin  >> e1;
            path = dirGraph->shortPath(e1);
            for(it=path->begin() ; it!=path->end();it++)
                cout << it->getValue() <<" " << it->getWeight()<<endl;
            break;
        case 9:
            dirGraph->reset();
            break;
        case 10:
            dirGraph->clear();
            break;
        case 11:
            exit=1;
            break;
    }
    return exit;
}

int executeActionGraph(int op, Graph *&graph){
    int exit=0;
    double w;
    string elem,e1,e2;
    list<Edge> *path; 
    list<Edge>::iterator it;
 //   treeNode<Type>* node;
    switch(op){
        case 1:
            if(graph->empty())
                cout << "Directed Graph is Empty" << endl;
            else
                cout  << "Directed Graph is NOT Empty"  << endl;
            break;
        case 2:
            cout  << "Degree(): " << graph->Degree(elem) << endl;
            break;
        case 3:
            cout << "Edge Count :" << graph->edgeCount() << endl;
            break;
        case 4:
            if(graph->isConnected())
                cout << "Is connected"<<endl;
            else
                cout << "Is NOT connected"<<endl;
                        
            break;
        case 5:
            cout << "Enter vertex a and b";
            cin  >> e1 >> e2;
            if(graph->adjacent(e1,e2)!=-1)
                cout << "Vertex are adjacent" << endl;
            else
                cout  << "Vertexes are not adjacent" << endl;
            break;
        case 6:
            cout << "Enter vertex: ";
            cin  >> e1;
            graph->DFS(e1);
            break;
        case 7:
            cout << "Enter vertex: ";
            cin  >> e1;
            graph->BFS(e1);
            break;
        case 8:
            cout << "Enter a vertex :";
            cin >> e1;
            graph->MST(e1);
            break;
        case 9:
            graph->clear();
            break;
        case 10:
            cout << "Enter values to be inserted(i.e A B 4.5): ";
            cin >> e1 >> e2 >> w;
            graph->insert(e1,e2,w);
            break;
        case 11:
            exit=1;
            break;
    }
    return exit;
}

void testDirGraph(){
    DirGraph graph;
    std::cout<< "Graph size : "<< graph.getHashTable()->getVertexCount() << std::endl;
    std::cout<< "Graph max size : "<< graph.getHashTable()->getMaxVertex() << std::endl;
//    for(int i=0; i<graph.getMaxVertex();i++){
//        std::cout << "Element : " << i << " with value: " << graph.getStatus()[i] << std::endl;
//        std::cout << graph.getVertex()[i].getValue() << std::endl;
//    }
    graph.printGraph();
    std::cout << "Number of edges : " <<graph.getHashTable()->getEdgeCount();
    std::cout << "Max Vertex : " <<graph.getHashTable()->getMaxVertex();
    //graph.reset();
    std::cout << "Indegree of  B: " << graph.inDegree("B") << endl;
    std::cout << "Indegree of  A: " << graph.inDegree("A") << endl;
    std::cout << "Indegree of  M: " << graph.inDegree("M") << endl;
    std::cout << "Outdegree of  B: " << graph.outDegree("B") << endl;
    std::cout << "Outdegree of  A: " << graph.outDegree("A") << endl;
    std::cout << "Outdegree of  M: " << graph.outDegree("I") << endl;
    
    std::cout << "A-A ->" << graph.adjacent("A","A") << endl;
    std::cout << "A-B ->" << graph.adjacent("A","B") << endl;
    std::cout << "A-M ->" << graph.adjacent("A","M") << endl;
    std::cout << "A-C ->" << graph.adjacent("A","C") << endl;
    std::cout << "2-C ->" << graph.adjacent("2","C") << endl;
    graph.printGraph();
    graph.DFS("A");
    graph.DFS("B");
    graph.DFS("C");
    graph.DFS("D");
    graph.DFS("E");
    graph.BFS("A");
    graph.BFS("B");
    graph.BFS("C");
    graph.BFS("D");
    graph.BFS("E");
    //list<string> sp = graph.shortPath("A","H");
    list<string>::iterator it;
    cout << "Path " ;
    //for(it=sp.begin(); it!=sp.end();it++)
      //  cout << "->" << *it;
    
    //sp = graph.shortPath("A","X");
    cout <<endl<< "Path " ;
    //for(it=sp.begin(); it!=sp.end();it++)
      //  cout << "->" << *it;
}
