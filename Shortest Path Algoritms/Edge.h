#ifndef EDGE_H
#define EDGE_H
#include <string>

using namespace std;

class Edge {
    string value;
    double weight;
    int taken;
public:
    Edge();
    Edge(string);
    Edge(string,double);
    //Edge(const Edge& orig);
    ~Edge();
    string getValue() const;
    void setValue(string);
    double getWeight()const;
    void setWeight(double);
    void setTaken(int taken);
    int getTaken() const;
};

Edge::Edge(){
    setValue("");
    setWeight(-1);
    setTaken(0);
}

Edge::Edge(string v){
    setValue(v);
    setWeight(-1);
    setTaken(0);
}

Edge::Edge(string v, double w){
    setValue(v);
    setWeight(w);
    setTaken(0);
}

Edge::~Edge(){

}

string Edge::getValue()const{
    return value;
}

void Edge::setValue(string v){
    this->value = v;
}

double Edge::getWeight()const{
    return weight;
}

void Edge::setWeight(double w){
    this->weight=w;
}

void Edge::setTaken(int taken) {
    this->taken = taken;
}

int Edge::getTaken() const {
    return taken;
}
#endif /* EDGE_H */

