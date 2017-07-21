#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

#include "Vertex.h"
#include "Edge.h"

using namespace std;

class HashTable {
    Vertex *vertex;
    int vertexCount;
    int maxVertex;
    int edgeCount;
public:
    static int v_modified;
    HashTable();
    HashTable(int);
    //HashTable(const HashTable& orig);
    virtual ~HashTable();
    
    void setVertex(Vertex* vertex);
    Vertex* getVertex() const;
    void setVertexCount(int vertexCount);
    int getVertexCount() const;
    void setMaxVertex(int maxVertex);
    int getMaxVertex() const;
    void setEdgeCount(int edgeCount);
    int getEdgeCount() const;

    
    int findVertex(string);
    
    void insertVertex(string);
    void insertEdge(string,string,double);
    int edgeExits(int ,string ,double);
    
    int hashFunction(string);
    int handleCollisionInsertion(int,string);
    int handleCollisionSearch(int,string);
};

HashTable::HashTable(){
    Vertex *new_vertex = new Vertex[19];
    setVertex(new_vertex);
    setVertexCount(0);
    setMaxVertex(19);
    setEdgeCount(0);
}

HashTable::HashTable(int n){
    Vertex *new_vertex = new Vertex[n];
    setVertex(new_vertex);
    setVertexCount(0);
    setMaxVertex(n);
    setEdgeCount(0);
}

HashTable::~HashTable(){
    delete[] vertex;
}

void HashTable::setVertex(Vertex* vertex){
    this->vertex = vertex;
}
Vertex* HashTable::getVertex() const{
    return vertex;
}

void HashTable::setVertexCount(int vertexCount){
    this->vertexCount = vertexCount;
}
int HashTable::getVertexCount() const{
    return vertexCount;
}

void HashTable::setMaxVertex(int maxVertex){
    this->maxVertex = maxVertex;
}
int HashTable::getMaxVertex() const{
    return maxVertex;
}

void HashTable::setEdgeCount(int edgeCount){
    this->edgeCount = edgeCount;
}
int HashTable::getEdgeCount() const{
    return edgeCount;
}

void HashTable::insertVertex(string v){
    int index = hashFunction(v);
    Vertex *aux_vertex = getVertex();
    if(aux_vertex[index].getKey()!= v){
        if(aux_vertex[index].getStatus()!=0)//handle collision
            index = handleCollisionInsertion(index,v);
        if(index !=-1){ //insert vertex
            //cout << v << " " << index <<endl;
            aux_vertex[index].setKey(v);
            aux_vertex[index].setStatus(1);      //is now occupied
            setVertexCount(getVertexCount()+1);
            HashTable::v_modified = 1;
        }
    }
    else
        cout << "Vertex already exists in list" << endl;
}

void HashTable::insertEdge(string a, string b, double w){
    int index,k;
    Vertex *aux_vertex=getVertex();
    index = hashFunction(a);
    if(aux_vertex[index].getStatus() !=0)
        index = handleCollisionSearch(index,a);
    if(index != -1){                            //vertex exists
        int found = edgeExits(index,b,w);
        if(!found){                             //edged does not exists
            Edge a(b,w);
            a.setTaken(0);
            list<Edge> *aux_edges = aux_vertex[index].getEdges();
            aux_edges->push_back(a);            //add new edge
            setEdgeCount(getEdgeCount()+1);
            HashTable::v_modified = 1;
        }
        else
            std::cout << "Edge: " << a <<"-"<<b <<"already exits." <<std::endl;
    }
    else
        std::cout << "Vertex: " << a << " does not exit" <<std::endl;
}

int HashTable::edgeExits(int index,string b,double w){
    int found=0;
    Vertex *aux_vertex= getVertex();
    list<Edge> *aux_edges = aux_vertex[index].getEdges();
    list<Edge>::iterator it;
    for(it = aux_edges->begin(); !found && it != aux_edges->end();it++){
        if(it->getValue() == b){
            it->setWeight(w);   //if edge exists override weight
            found =1;
        }
    }
    return found;
}

int HashTable::hashFunction(string v){
    int res;
        int i,max=getMaxVertex(),found =0;
        Vertex *aux_ver = getVertex();
        //conversion
        int key=0;
        for(i=0;i<v.size();i++)
            key+=v[0];
        //compression
        res = key % max;
    return res;
}

int HashTable::handleCollisionInsertion(int res,string v){
//    std:: cout << "handleCoollisionInsertion()" << std::endl;
    int found=0,available =0, max = getMaxVertex();
    int stat,key;
    string val;
    Vertex *aux_ver = getVertex();
    while(((stat=aux_ver[res].getStatus())!=0) && !found && !available){
        val = aux_ver[res].getKey();
        found = stat==1 && val==v ;   //
        if(!found){
            available = stat==-1;
            if(!available){
                key=(res + 13);
                res =  key % max;                //find new position                //find new position
            }
        }
    }
    if(found){                    //vertes was already inserted
        res = -1;
        cout << "Vertex: "<< v <<" already in the list" << endl;
    }
    return res;
}

int HashTable::handleCollisionSearch(int res,string v){
//    std:: cout << "handleCoollisionSearch()" << std::endl;
    int found=0, key = res,max= getMaxVertex(),numb=0;
    Vertex *aux_ver = getVertex();
    while(aux_ver[res].getStatus()!=0 && !found && (numb<getMaxVertex())){
        found =aux_ver[res].getKey() == v && aux_ver[res].getStatus()==1;   //
        if(!found){
            key=(res + 13);
            res =  key % max;                //find new position
            numb++;
        }
    }
    if(!found)                    //Vertex not found in the list
        res = -1;
    return res;
}


int HashTable::findVertex(string v){
//    try{
    Vertex *aux_vertex = getVertex();
    int index=hashFunction(v);
    if(aux_vertex[index].getKey() != v)
        index = handleCollisionSearch(index,v);
//    if(index==-1)
//        throw std::invalid_argument("No Vertex found in the List");
    return index;
//    }catch(const std::invalid_argument &e){
//        cout << "findVertex() -> " << e.what()<< endl;
//    }
}
int HashTable::v_modified = 0;
#endif /* HASHTABLE_H */

