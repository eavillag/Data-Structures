#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <stdexcept>
#include <float.h>

#include "HashTable.h"

using namespace std;

class Graph {
    HashTable *hashTable;
public:
    Graph();
    virtual ~Graph();

    HashTable* getHashTable();
    void setHashTable(HashTable *);
    bool empty();
    int Degree(string);
    int edgeCount();
    bool isConnected();
    int isConnectedRecursive(int );
    double adjacent(string,string);
    void DFS(string);
    void DFSRecursive(string );
    void BFS(string);
    
    void MST(string);
    void initializeArrays(HashTable *,int *&,int *&, double *&,int*&,string);
    int FindMinimumEdge(int*,double *,int *,int);
    void markEdgeTaken(int , int);
    int findEdgePosition(int *vertex,int j,int size);
    void updateNewEdgesVertex(HashTable *,int ,int *,double *,int *,int*,int);
    void setMinimumEdgeWeight(int ,int *,int *,double *,int*,int);
    void printfShortestEdge(int index,int *vertex,int *edge,double*);
    void resetTaken();
    
    void buildGraph();
    void readVertexes(ifstream &);
    void readEdges(ifstream &);
    void printGraph();
    
    void clear(); 
    void reset();
    void insert(string, string, double);
    void deleteEdge(string ,string);
};

Graph::Graph(){
    setHashTable(new HashTable());
    buildGraph();

}
Graph::~Graph(){
    delete[] hashTable;
}

HashTable* Graph::getHashTable(){
    return hashTable;
}

void Graph::setHashTable(HashTable *h){
    this->hashTable = h;
}

bool Graph::empty(){
    return getHashTable()->getVertexCount()==0;
}

int Graph::Degree(string v){
    try{
        int deg=-1,index = getHashTable()->findVertex(v);
        if(index != -1){
            Vertex *aux_vertex = getHashTable()->getVertex();
            deg = aux_vertex[index].getEdges()->size();
        }else
            throw std::invalid_argument("Vertex not in the List");
        return deg;
    }catch(const std::invalid_argument &e){
        std::cout << e.what() << endl;
        return -1;
    }
}

double Graph::adjacent(string a,string b){
    try{
        double weight=-1;
        int index = getHashTable()->findVertex(b);
        if(index!=-1){ //Found vertex
            index = getHashTable()->findVertex(a);
            if(index!=-1){
                if(a==b)
                    weight =0;
                else{
                    int found=0;
                    Vertex *aux_vertex = getHashTable()->getVertex();
                    list<Edge> *aux_edges = aux_vertex[index].getEdges();
                    list<Edge>::iterator it;
                    for(it = aux_edges->begin(); it != aux_edges->end() && !found; it++)
                        found = it->getValue() == b;
                    if(found)
                        weight = (--it)->getWeight();
                    else//Vertex does not exists
                        throw std::invalid_argument("Vertexes are not adjacent");
                }
            }else//Vertex does not exists
                throw std::invalid_argument("Vertex not in the list");
        }else//Vertex does not exists
            throw std::invalid_argument("Vertex not in the list");
        return weight;
    }catch(const std::invalid_argument &e){
        cout << "adjacent() : "<< e.what() << endl;
        return -1;
    }
}

int Graph::edgeCount(){
    return getHashTable()->getEdgeCount();
}

bool Graph::isConnected(){
    int i,count=0,found=0;
    Vertex *aux_vertex = getHashTable()->getVertex();
    list<Edge>::iterator it;
    for(i = 0 ; i<getHashTable()->getMaxVertex()&& !found;i++)
        found = aux_vertex[i].getStatus()==1 && aux_vertex[i].getVisited()==0;
    count = isConnectedRecursive(--i);
    reset();
    //cout << count<<endl;
    return count==(getHashTable()->getVertexCount()-1);
}

int Graph::isConnectedRecursive(int index){
    Vertex * aux_vertex = getHashTable()->getVertex();
    aux_vertex[index].setVisited(1);
    list<Edge> *aux_edges = aux_vertex[index].getEdges();
    list<Edge>::iterator it;
    for(it=aux_edges->begin(); it!=aux_edges->end(); it++){
        index = getHashTable()->findVertex(it->getValue());
        if(aux_vertex[index].getVisited()==0)
            return 1 + isConnectedRecursive(index);
    }
    return 0;
    
}
void Graph::DFS(string v){
    try{
        int index=getHashTable()->findVertex(v);
        if(index!=-1){
            getHashTable()->getVertex()[index].setVisited(1);
            DFSRecursive(v);
            cout << endl;
            reset();
        }else
            throw std::invalid_argument("Vertex does not exist");
    }catch(const std::invalid_argument &e){
        cout << "DFS() : "<< e.what() << endl;
    }
}

void Graph::DFSRecursive(string v){
    string val;
    int index = getHashTable()->findVertex(v);
    cout << v << endl;   
    stack<string> stack_vertex;
    list<Edge> *aux_edges = getHashTable()->getVertex()[index].getEdges();
    list<Edge>::iterator it;
    for(it=aux_edges->begin();it!=aux_edges->end();it++){
        val = it->getValue();
        index = getHashTable()->findVertex(val);
        if(getHashTable()->getVertex()[index].getVisited()==0){
            getHashTable()->getVertex()[index].setVisited(1);
            DFSRecursive(val);
        }
    }
}

void Graph::BFS(string v){
    try{
        int index = getHashTable()->findVertex(v);
        if(index != -1){
            queue<string> queue_vertex;
            string val;
            list<Edge> *aux_edges;
            list<Edge>::iterator it;
            queue_vertex.push(v);
            while(!queue_vertex.empty()){
                val=queue_vertex.front();
                queue_vertex.pop();
                index = getHashTable()->findVertex(val);
                getHashTable()->getVertex()[index].setVisited(1);
                aux_edges = getHashTable()->getVertex()[index].getEdges();
                for(it=aux_edges->begin();it!=aux_edges->end();it++){
                    index = getHashTable()->findVertex(it->getValue());
                    if(getHashTable()->getVertex()[index].getVisited()==0){
                        queue_vertex.push(it->getValue());
                        getHashTable()->getVertex()[index].setVisited(1);
                    }
                }
            }
            reset();
        }else
            throw std::invalid_argument("Vertex does not exist");
    }catch(const std::invalid_argument &e){
        cout << "BFS() : "<< e.what() << endl;
    }
}

void Graph::MST(string v){
   // cout << "MST()"<<endl;
    if(isConnected()){
        HashTable *new_ht= new HashTable();
        int *vertex,index,i,*edge,*pos;
        double *weight;
        initializeArrays(new_ht,vertex,edge,weight,pos,v);
        for(i=1;i<getHashTable()->getVertexCount();i++){
//            cout << "ITERATION: " <<i <<endl;
            index = FindMinimumEdge(vertex,weight,edge,i);   //find min edge among vertexes
            if(index !=-1){
                printfShortestEdge(index,vertex,edge,weight);  //print the shortest edge
                markEdgeTaken(vertex[index],edge[index]);      //mark edge as taken
                markEdgeTaken(edge[index],vertex[index]);
                updateNewEdgesVertex(new_ht,index,vertex,weight,edge,pos,i); //update vertex
                setMinimumEdgeWeight(index,vertex,edge,weight,pos,i);        //find min edge for vertex
                setMinimumEdgeWeight(i,vertex,edge,weight,pos,i);
            }
        }
        delete vertex;
        delete pos;
        delete weight;
        delete edge;
        resetTaken();
    }else
        cout << "Graph is not Connected. No MST can be found" << endl;
}

void Graph::initializeArrays(HashTable *new_ht,int *&vertex,int*&edge,double *&weight,int*&pos,string v){
    int size =getHashTable()->getVertexCount(),index;
    vertex = new int[size];                      //allocate memory
    edge  = new int[size];
    pos  = new int[size];
    weight = new double[size];
    for(int i=0;i<size;i++){                     //initialize arrays
        edge[i]=-1;
        pos[i]=-1;
        weight[i]=-1;
    }
    Vertex *aux = getHashTable()->getVertex();
    Vertex *new_vertex = new_ht->getVertex();
    for(int i=0;i<getHashTable()->getMaxVertex();i++){ //copy the current table to a new table.
        if(aux[i].getStatus()==1){
            new_vertex[i].setKey(aux[i].getKey());     //not the list<Edge> member
            new_vertex[i].setStatus(1);
        }
    }
    index = new_ht->findVertex(v);//find position of vertex v in the table
    vertex[0]=index;              //set Vertex v in the first position of the array
    setMinimumEdgeWeight(0,vertex,edge,weight,pos,0);
    markEdgeTaken(edge[0],vertex[0]);
}

int Graph::FindMinimumEdge(int *vertex,double *weight,int *edge,int size){
//    cout << "FindMinimumEdge()"<<endl;
    int j,min_index=-1,pos;
    double min=DBL_MAX;
    for(j=0; j < size ;j++){
        if(weight[j]>0 && min>weight[j]){
            pos = findEdgePosition(vertex,edge[j],size);
//            cout << "POS: " << pos<<endl;
            if(pos==-1){
                min=weight[j];
                min_index = j;
            }
        }
    }
    return min_index;
}

void Graph::markEdgeTaken(int a, int b){
//    cout << "markEdgeTaken()"<<endl;
    int found=0;
    Vertex *aux_vertex = getHashTable()->getVertex();
    string value = aux_vertex[b].getKey();
    list<Edge> *aux_edges = aux_vertex[a].getEdges();
    list<Edge>::iterator it;
    for(it=aux_edges->begin();it!=aux_edges->end() && !found;it++){
        found = it->getValue() == value;
    }
    if(found)
        (--it)->setTaken(1);
}
void Graph::updateNewEdgesVertex(HashTable *new_ht,int index,int *vertex,double *weight,int *edge,int *pos,int size){
//    cout << "updateNewEdgesVertex()"<<endl;
    Vertex *aux_vertex = getHashTable()->getVertex();
    vertex[size]=edge[index];
    pos[index] = size;
    string a,b;
    double w;
    a = aux_vertex[vertex[index]].getKey();
    b = aux_vertex[edge[index]].getKey();
    w = weight[index];
    new_ht->insertEdge(a,b,w);
    new_ht->insertEdge(b,a,w);
}

void Graph::setMinimumEdgeWeight(int index,int *vertex,int *edge,double *weight,int* pos,int size){
//    cout << "setMinimumEdgeWeight()"<<endl;
    int j;
    double min=DBL_MAX;
    string v;
    Vertex *aux_vertex = getHashTable()->getVertex();
    list<Edge> *aux_edges = aux_vertex[vertex[index]].getEdges();
    list<Edge>::iterator it, ot;
    for(it=aux_edges->begin(); it!=aux_edges->end();it++){//find minimum edge and weight
//        cout << it->getWeight() << " " << it->getValue() << " " << it->getTaken()<<endl;
        if(it->getWeight()< min && it->getTaken()==0){ //if minimum and not taken yet
            min = it->getWeight();                     //update minimum info
            v = it->getValue();
            ot=it;
//            cout << min <<" "<<v<<endl;
        }
    }
    if(min == DBL_MAX){  //all edges of the vertex in stored in index are taken
//        cout << "ENTER CLOSED PATH" <<endl;
        edge[index]=-1;  // all edges taken
        pos[index]=-1;    //no edge then set to -1
        weight[index]=-1; //
    }else{                                 //there is still a minimum edge
//        cout << "Minimun Edge"<< aux_vertex[vertex[index]].getKey();
//        cout << "->"<< v <<endl;
        j = getHashTable()->findVertex(v); //find index of edge in vertex
        edge[index]=j;                     //store the index of vertex v that constitutes the edge
        weight[index]=min;                 //store the weight of the edge
        j = findEdgePosition(vertex,j,size);  //find the position where the index of edge should be
        pos[index]=j;                      //update position of the edge in pos
        ot->setTaken(1);               //edge taken 
    }
}

void Graph::printfShortestEdge(int index,int *vertex,int *edge, double *weight){
//    cout << "printfShortestEdge()"<<endl;
    Vertex *aux_vertex = getHashTable()->getVertex();
    cout << aux_vertex[vertex[index]].getKey() << " " << aux_vertex[edge[index]].getKey() << " " << weight[index]<<endl;
}
int Graph::findEdgePosition(int *vertex,int pos,int size){
    int i,index=-1,found=0;
    for(i=0;i<size && !found;i++) //search linearly through the array
        found = pos==vertex[i] ;   //for the index of vertex v(pos)
    if(found)
        index=--i;
    return index;
}

void Graph::buildGraph(){
    string fname;
    std:: cout << "Enter the name of the file" << std::endl;
    std::cin >>fname;
    ifstream input;
    input.open(fname.c_str(),ios::in);
    if(input){
        readVertexes(input);
        readEdges(input);  
        input.close();
    }
}

void Graph::readVertexes(ifstream &input){
    char c;
    string a;
    input.get(c);
    while(c!='\n'){  //read vertex
        input.unget();
        input >> a;
        getHashTable()->insertVertex(a);
        input.get(c);
    }
}

void Graph::readEdges(ifstream &input){
    int max=getHashTable()->getMaxVertex();
    double w;
    string a,b;
    while(!input.eof() && max>=(getHashTable()->getVertexCount()+1)){//insert edges
        input >> a >> b >> w;
        getHashTable()->insertEdge(a,b,w);
        getHashTable()->insertEdge(b,a,w);
    }   
}

void Graph::printGraph(){
    Vertex *aux_vertex = getHashTable()->getVertex();
    list<Edge> *aux_edges;
    for(int i=0; i<getHashTable()->getMaxVertex();i++){
        if(aux_vertex[i].getStatus()==1){
            aux_edges = aux_vertex[i].getEdges();
            std::cout << "Vertex : " << aux_vertex[i].getKey()<<" Key: " << aux_vertex[i].getKey()<< std::endl;
            std::cout << "Visited? : " << aux_vertex[i].getVisited() << endl;
            std:: cout << "Edges: ";
            for(list<Edge>::iterator it=aux_edges->begin(); it!= aux_edges->end();it++)
                std:: cout << it->getValue() << " " << it->getWeight()<< std::endl; 
        }
    }        
}

void Graph::clear(){
    Vertex *aux_vertex = getHashTable()->getVertex();
    list<Edge> *aux_edges;
    for(int i=0; i<getHashTable()->getMaxVertex();i++){
        if(aux_vertex[i].getStatus()==1){
            aux_edges = aux_vertex[i].getEdges();
//            std::cout << "Clearing Vertex Key: " << aux_vertex[i].getKey()<< std::endl;
            aux_vertex[i].setEdges(NULL);
            aux_vertex[i].setKey("");
            aux_vertex[i].setStatus(0);
            aux_vertex[i].setVisited(0);
            delete aux_edges;
            std::cout << std::endl;
        }
    }        
    getHashTable()->setVertexCount(0);
    getHashTable()->setEdgeCount(0);
}


void Graph::reset(){
    Vertex *aux_vertex = getHashTable()->getVertex();
    for(int i=0;i<getHashTable()->getMaxVertex();i++)
        aux_vertex[i].setVisited(0);
}

void Graph::resetTaken(){
    Vertex *aux_vertex = getHashTable()->getVertex();
    for(int i=0;i<getHashTable()->getMaxVertex();i++){
        if(aux_vertex[i].getStatus()==1){
            list<Edge>::iterator it;
            list<Edge> *aux_edges = aux_vertex[i].getEdges();
            for(it=aux_edges->begin(); it!=aux_edges->end();it++)
                it->setTaken(0);
        }
    }
}

void Graph::insert(string a, string b, double w){
    try{
        if(w<0 || a==b){
            throw std::invalid_argument("The weight is a negative number");
        }
        if(w==0){
            deleteEdge(a,b);
            deleteEdge(b,a);
        }else{
            getHashTable()->insertEdge(a,b,w);
            getHashTable()->insertEdge(b,a,w);
        }
    }catch (const std::invalid_argument &e){
        std::cout << e.what() << endl;
    }
}

void Graph::deleteEdge(string a,string b){
    try{
        Vertex *aux_vertex = getHashTable()->getVertex();
        int index = getHashTable()->findVertex(a);
        if(index !=-1){
            int found=0;
            list<Edge>::iterator it;
            list<Edge> *aux_edges = aux_vertex[index].getEdges();
            for(it=aux_edges->begin(); it!=aux_edges->end()&& !found;it++){
                found =it->getValue() == b;
                if(found){
                    aux_edges->erase(it);
                    getHashTable()->setEdgeCount(getHashTable()->getEdgeCount()-1);
                }
            }
        }else
            throw std::invalid_argument("Edge does not exists");
    }catch(const std::invalid_argument &e){
        std::cout << e.what() << endl;
    }
}
#endif /* GRAPH_H */

