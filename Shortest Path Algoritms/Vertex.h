#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <list>
#include "Edge.h"
using namespace std;

class Vertex {
    string key;
    list<Edge> *edges;
    int visited;   // 1=visited, 0=not visited
    int status;    //-1=available, 0=empty,1=occupied;
public:
    Vertex();
    Vertex(string);
    //Vertex(const Vertex& orig);
    ~Vertex();
    
    void setKey(string k);
    string getKey();
    void setEdges(list<Edge> *);
    list<Edge> * getEdges();
    void setVisited(int);
    int getVisited();
    void setStatus(int);
    int getStatus();

};
Vertex::Vertex(){
    setKey("");
    setEdges(new list<Edge>);
    setVisited(0);
    setStatus(0);
}
Vertex::Vertex(string v){
    setKey(v);
    setEdges(new list<Edge>);
    setVisited(0);
    setStatus(0);
}
//Vertex(const Vertex& orig);
Vertex::~Vertex(){
    
}

void Vertex::setKey(string k){
    this->key =k;
}
string Vertex::getKey(){
    return key;
}
void Vertex::setEdges(list<Edge> *e){
    this->edges = e;
}
list<Edge> * Vertex::getEdges(){
    return edges;

}
void Vertex::setVisited(int v){
    this->visited = v;
}
int Vertex::getVisited(){
    return visited;
}
void Vertex::setStatus(int s){
    this->status = s;
}
int Vertex::getStatus(){
    return status;
}
#endif /* VERTEX_H */

