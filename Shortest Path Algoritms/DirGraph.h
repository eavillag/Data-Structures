#ifndef DIRGRAPH_H
#define DIRGRAPH_H

#include <string>
#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <float.h>
#include <fstream>
#include <stdexcept>
#include "HashTable.h"
#include "Edge.h"

using namespace std;

class DirGraph {
    HashTable *hashTable;
public:
    
    DirGraph();
    DirGraph(const DirGraph& orig);
    virtual ~DirGraph();

    static string v_a;
    static string v_b;
    static list<string> v_path;
    static double v_dist;
    //static int v_modified;
    HashTable* getHashTable();
    void setHashTable(HashTable *);
    bool empty();
    //int findVertex(string,int &);
    int inDegree(string);
    int outDegree(string);
    double adjacent(string,string);
    int edgeCount();
    void DFS(string);
    void DFSRecursive(string );
    void BFS(string);
    list<Edge>* shortPath(string);
    list<string> shortPath(string,string);
    void initializeArrays(double *&, int *&,int,int *&);
    int findMinimumDistance(double *,int *);
    void updateDistance(double *, int *,int );
    void printArrayValues(double *dist, int *pred);
    
    double distance(string,string);

    void buildGraph();
    void readVertexes(ifstream &);
    void readEdges(ifstream &);
    void printGraph();
    
    void clear();
    void reset();
    void insert(string, string, double);

};
DirGraph::DirGraph(){
    setHashTable(new HashTable());
    buildGraph();
}


DirGraph::~DirGraph(){
    delete hashTable;
}

HashTable* DirGraph::getHashTable(){
    return hashTable;
}

void DirGraph::setHashTable(HashTable *h){
    this->hashTable = h;
}

bool DirGraph::empty(){
    return getHashTable()->getVertexCount()==0;
}

int DirGraph::inDegree(string v){
    cout << "inDegree()" <<endl;
    int count=0,found;
    Vertex *aux_vertex = getHashTable()->getVertex();
    list<Edge> *aux_edges;
    for(int i=0; i<getHashTable()->getMaxVertex(); i++){
        if((aux_vertex[i].getStatus() == 1) && (aux_vertex[i].getKey()!= v)){
           // cout << "Cheking vertex : " << aux_vertex[i].getValue() << endl;
            aux_edges = aux_vertex[i].getEdges();
            list<Edge>::iterator it;
            found=0;
            for(it = aux_edges->begin();!found && it!= aux_edges->end(); it++ ){
                found = it->getValue() == v;
                if(found)
                    count+=1;
            }
        }
    }
    return count;
}

int DirGraph::outDegree(string v){
    int deg=-1,index = getHashTable()->findVertex(v);
    Vertex *aux_vertex = getHashTable()->getVertex();
    if(index != -1)
        deg = aux_vertex[index].getEdges()->size();
    else
        std::cout << "Vertex not in the List" << std::endl;
    return deg;
}

double DirGraph::adjacent(string a,string b){
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

int DirGraph::edgeCount(){
    return getHashTable()->getEdgeCount();
}
void DirGraph::DFS(string v){
    cout << "DFS()" << endl;
    int index=getHashTable()->findVertex(v);
    if(index!=-1){
        getHashTable()->getVertex()[index].setVisited(1);
        DFSRecursive(v);
        cout << endl;
        reset();
    }
    else
        cout<< "Vertex " << v << "does not exist" <<endl;
}

void DirGraph::DFSRecursive(string v){
    cout << "DFSRecursieve()" << endl;
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
            //stack_vertex.push(it->getValue());
            getHashTable()->getVertex()[index].setVisited(1);
            DFSRecursive(val);
        }
    }
//    while(!stack_vertex.empty()){
//        val = stack_vertex.top();
//        stack_vertex.pop();
//        DFSRecursive(val);
//    }
}

void DirGraph::BFS(string v){
    cout << "BFS()" << endl;
    int index = getHashTable()->findVertex(v);
    if(index != -1){
        //getHashTable()->getVertex()[index].setVisited(1);
        //cout << v <<endl;
        queue<string> queue_vertex;
        string val;
        list<Edge> *aux_edges;
        list<Edge>::iterator it;
        queue_vertex.push(v);
//        aux_edges = getHashTable()->getVertex()[index].getEdges();
//        for(it=aux_edges->begin();it!=aux_edges->end();it++){
//            index = getHashTable()->findVertex(it->getValue());
//            if(getHashTable()->getVertex()[index].getVisited()==0){
//                queue_vertex.push(it->getValue());
//                getHashTable()->getVertex()[index].setVisited(1);
//            }
//        }
        while(!queue_vertex.empty()){
            val=queue_vertex.front();
            queue_vertex.pop();
            cout <<val << endl;
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
    }
}


list<Edge>* DirGraph::shortPath(string a){
    int index_a = getHashTable()->findVertex(a);
    list<Edge> *path = new list<Edge>();
    if(index_a !=-1){
        double *dist;
        int *pred,*ind_vertex,ind_aux=0;
        Vertex *aux_vertex = getHashTable()->getVertex();
        initializeArrays(dist,pred,index_a,ind_vertex);
        for(int i=1; (i<getHashTable()->getVertexCount()) && ind_aux!=-1 /*&& (aux_vertex[index_b].getVisited()==0)*/;i++){
            ind_aux = findMinimumDistance(dist,ind_vertex);
            if(ind_aux !=-1){
                getHashTable()->getVertex()[ind_aux].setVisited(1);
                updateDistance(dist, pred,ind_aux);
            }
        }
        for(int i=0;i<getHashTable()->getVertexCount();i++){
            ind_aux = ind_vertex[i];
            if(dist[ind_aux]!=-1){
                Edge a(aux_vertex[ind_aux].getKey(),dist[ind_aux]);
                path->push_front(a);
            }
        }
    }else
        cout << "Vertex " <<a <<" does not exist"<<endl;
    reset();
    return path;
}

list<string> DirGraph::shortPath(string a,string b){
    cout << "shortPath()" << endl;
    if(!HashTable::v_modified && v_a==a && v_b==b);
       return v_path;
    int index_a = getHashTable()->findVertex(a);
    list<string> path;
    if(index_a !=-1){
        int index_b = getHashTable()->findVertex(b);
        if(index_b !=-1){
            if(a==b)
                cout << "Vertex are the same" << endl;
            else{
                double *dist;
                int *pred,*ind_vertex,ind_aux=0;
                Vertex *aux_vertex = getHashTable()->getVertex();
                initializeArrays(dist,pred,index_a,ind_vertex);
                for(int i=1; (i<getHashTable()->getVertexCount()) && ind_aux!=-1 && (aux_vertex[index_b].getVisited()==0);i++){
                    ind_aux = findMinimumDistance(dist,ind_vertex);
                    if(ind_aux !=-1){
                        getHashTable()->getVertex()[ind_aux].setVisited(1);
                        updateDistance(dist, pred,ind_aux);
                    }
                }
                if(dist[index_b]!=-1){
                    while(ind_aux != -1){
                        path.push_front(aux_vertex[ind_aux].getKey());
                        ind_aux = pred[ind_aux];
                    }
                }else
                    cout << "Vertexes are not connected" << endl;
                v_dist = dist[index_b];
                v_path=path;
                v_a=a;
                v_b=b;
                HashTable::v_modified=0;
            }
        }else
            cout<<"Vertex " <<b <<" does not exist"<<endl;
    }else
        cout << "Vertex " <<a <<" does not exist"<<endl;
    reset();
    return path;
}

void DirGraph::initializeArrays(double *&dist, int *&pred,int index,int *&ind_vertex){
    cout << "initializeArrays()" << endl;
    dist = new double[getHashTable()->getMaxVertex()];
    pred= new int[getHashTable()->getMaxVertex()];
    ind_vertex = new int[getHashTable()->getVertexCount()];
    Vertex *aux_vertex = getHashTable()->getVertex();
    for(int i=0,j=0;i<getHashTable()->getMaxVertex();i++){
        dist[i]=-1;
        pred[i]=-1;
        if(aux_vertex[i].getStatus()==1)
            ind_vertex[j++]=i;
    }
    dist[index]=0;
    pred[index]=-1;
    aux_vertex[index].setVisited(1);
    updateDistance(dist, pred,index);
}

int DirGraph::findMinimumDistance(double *dist,int *ind_vertex){
    cout << "findMinimumDistance()" << endl;
    int min_index=-1,j;
    double min=DBL_MAX;
    Vertex *aux_vertex = getHashTable()->getVertex();
    for(int i=0;i<getHashTable()->getVertexCount();i++){
        j=ind_vertex[i];
        if(aux_vertex[j].getVisited()==0 && dist[j]!=-1 && dist[j]<min){
            min = dist[j];
            min_index = j;
        }
    }
    //cout << "MINIMUM -> " << aux_vertex[min_index].getKey()<<endl;
    return min_index;
}

void DirGraph::updateDistance(double *dist, int *pred,int index){
    cout << "updateDistance()" << endl;
    int j,new_dist=0;
    Vertex *aux_vertex = getHashTable()->getVertex();
    list<Edge> *aux_edges = aux_vertex[index].getEdges();
    list<Edge>::iterator it;
    for(it = aux_edges->begin(); it!=aux_edges->end(); it++){
        j = getHashTable()->findVertex(it->getValue());
        if(aux_vertex[j].getVisited()== 0){
            cout << it->getValue() << endl;
            if(dist[j] == -1){
                dist[j]=dist[index]+it->getWeight();
                pred[j] = index;
            }else{
                new_dist = dist[index]+it->getWeight();
                if( new_dist < dist[j]){
                    dist[j] = new_dist;
                    pred[j] = index;
                }
            }
        }
    }
}

double DirGraph::distance(string a,string b){
    int dist;
    if(!HashTable::v_modified && v_a==a && v_b==b){
        return v_dist;
    }else
        shortPath(a,b);
    HashTable::v_modified =0;
    return dist;
    
}

void DirGraph::printArrayValues(double *dist, int *pred){
    cout << "printArrayValues()" << endl;
    for(int i=0; i<getHashTable()->getMaxVertex();i++)
        cout << dist[i] << " " << pred[i] << endl;
}
void DirGraph::buildGraph(){
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

void DirGraph::readVertexes(ifstream &input){
    std:: cout << "readVertexes()" << std::endl;
    char c;
    string a;
    input.get(c);
    int index,k;
    while(c!='\n'){  //read vertex
        input.unget();
        input >> a;
        getHashTable()->insertVertex(a);
        input.get(c);
    }
}

void DirGraph::readEdges(ifstream &input){
    std:: cout << "readEdges()" << std::endl;
    int max=getHashTable()->getMaxVertex();
    double w;
    string a,b;
    while(!input.eof() && max>=(getHashTable()->getVertexCount()+1)){//insert edges
        input >> a >> b >> w;
        getHashTable()->insertEdge(a,b,w);
    }   
}

void DirGraph::printGraph(){
    std:: cout << "printGraph()" << std::endl;
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
//            std::cout << std::endl;
        }
    }        
}

void DirGraph::clear(){
    std:: cout << "clear()" << std::endl;
    Vertex *aux_vertex = getHashTable()->getVertex();
    list<Edge> *aux_edges;
    for(int i=0; i<getHashTable()->getMaxVertex();i++){
        if(aux_vertex[i].getStatus()==1){
            aux_edges = aux_vertex[i].getEdges();
            std::cout << "Clearing Vertex Key: " << aux_vertex[i].getKey()<< std::endl;
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


void DirGraph::reset(){
    Vertex *aux_vertex = getHashTable()->getVertex();
    for(int i=0;i<getHashTable()->getMaxVertex();i++)
        aux_vertex[i].setVisited(0);
}

void DirGraph::insert(string a, string b, double w){
    getHashTable()->insertEdge(a,b,w);
}

string DirGraph::v_a="";
string DirGraph::v_b="";
list<string> DirGraph::v_path;
double DirGraph::v_dist=0;
#endif /* DIRGRAPH_H */

