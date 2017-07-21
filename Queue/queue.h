#ifndef QUEUE_H
#define QUEUE_H

#include <string.h>
#include <iostream>
#include <iomanip>
#include <stdexcept>

typedef std::string Type;

class queue{
    Type *array;
    int iHead;
    int iTail;
    int count;
    int initialSize;
    int arraySize;
public:
    queue(int n=15);
    virtual ~queue();

    void setArray(Type* array);
    Type* getArray() const;
    void setIHead(int iHead);
    int getIHead() const;
    void setITail(int iTail);
    int getITail() const;
    void setCount(int count);
    int getCount() const;
    void setInitialSize(int initialSize);
    int getInitialSize() const;
    void setArraySize(int arraySize);
    int getArraySize() const;

    Type front() const;
    Type back() const;
    int size() const;
    bool empty() const;
    int capacity() const;
    void display();

    void enqueue(Type const &);
    Type dequeue();
    void clear();
};

queue::queue(int n){
    try{
        int i=n;
        if(n<=0)               //if n is negative or zero
            i=1;               //set array size and capacity to 1
        setArray(new Type[i]);
        setCount(0);
        setIHead(-1);
        setITail(-1);
        setArraySize(i);
        setInitialSize(i);
    }catch(const std::exception &e){
        std::cout << "Error Constructor" <<std::endl;
    }
}
queue::~queue(){
    delete [] array;
}

void queue::setArray(Type* array) {
    this->array = array;
}
Type* queue::getArray() const {
    return array;
}

void queue::setIHead(int iHead) {
    this->iHead = iHead;
}
int queue::getIHead() const {
    return iHead;
}
void queue::setITail(int iTail) {
    this->iTail = iTail;
}
int queue::getITail() const {
    return iTail;
}

void queue::setCount(int count) {
    this->count = count;
}
int queue::getCount() const {
    return count;
}

void queue::setInitialSize(int initialSize) {
    this->initialSize = initialSize;
}
int queue::getInitialSize() const {
    return initialSize;
}

void queue::setArraySize(int arraySize) {
    this->arraySize = arraySize;
}
int queue::getArraySize() const {
    return arraySize;
}

//Front() will return the value at the front of the queue
//or throw an exception when queue is empty
Type queue::front() const{
    try{
        if(empty())                 //if array empty throw exception
            throw std::underflow_error("Error: Queue is Empty");
        return getArray()[getIHead()];//else return value
    }catch(std::underflow_error e){
        Type exit;
        std::cout << e.what() << std::endl;
        return exit; //return value so that program does not terminate
    }

}

//Back() will return the value at the end of the queue
//or throw an exception when queue is empty
Type queue::back() const{
    try{
        if(empty())    //if array empty throw exception
            throw std::underflow_error("Error: Queue is Empty");
	else
            return getArray()[getITail()];//return value at the end
    }catch(std::underflow_error e){
        Type exit;
        std::cout << e.what() << std::endl;
        return exit; //return any value so that program does not terminate
    }
}
int queue::size() const{
    return getCount();
}
bool queue::empty() const{
    return getCount()==0;
}
int queue::capacity() const{
    return getArraySize();
}

//display will show the elements that are store in the queue
//from head to tail
void queue::display(){
    int t;
    if(empty())
        std::cout << "Queue is empty." << std::endl;
    else{
        for(int i=getIHead(),c=0; ((t=i%getArraySize()) != getITail()) && (c < getCount()); i++,c++)
            std::cout << t <<" : " << getArray()[t]<<std::endl;
        std::cout << t <<" : " << getArray()[t]<<std::endl;
    }

}

//enqueue() will store a new value onto the queue at the end
void queue::enqueue(Type const &val){
    try{
        if(empty()){ //if queue is empty
            setITail(0);
            setIHead(0);
            getArray()[0] = val;
            setCount(1);
        }else{       //if queue has elements
            int t,s,c;
            if((c=getCount()) == (s=getArraySize())){ // if the queue is full
                setArraySize(s*2); //duplicate size of queue
                Type *new_array = new Type[getArraySize()],*arr = getArray();
                int i,j,b; //allocate memory
                for(i=getIHead(),j=0; (t=i%s) != (b=getITail()); j++, i++)
                    new_array[j] = arr[t]; //update new queue
                new_array[j]= arr[getITail()]; //copy last value of the queue
                delete []arr; //deallocate old queue
                setArray(new_array); //set new queue
                setITail(++j); //set new tail index
                setIHead(0);   //set head index
            }else// if queue is not full
                setITail((++(t=getITail()))%s); //set new tail pointer
            getArray()[getITail()]=val;  //set new value at the end of queue
            setCount(++c);               //set new count/size of queue
        }
    }catch(const std::exception &e){
        throw e.what();
    }
}
Type queue::dequeue(){
    try{
        if(empty())  //if queue is empty throw exception
            throw std::underflow_error("Error. Empty Queue");
        Type e = front();
        int c,s,h;
	h=getIHead();     //get head index
	s=getArraySize(); //get array size
        h=(h+ 1+ s)% s;   // set new head index
        //if queue has less than 1/4 original size and > initial capacity
        if(((--(c=getCount())) == ((s=getArraySize())/4)) && (s>getInitialSize())){
            setArraySize(s/2); //halve queue size
            Type *new_array = new Type[getArraySize()],*arr = getArray();
            int i,j,m;         //set new queue
            for(i=h,j=0; (m=i%s) != getITail(); j++, i++)
                new_array[j] = arr[m];   //copy values to new queue
            new_array[j]= arr[m];        //copy last value to new queue
            delete []arr;                //deallocate old queue
            setArray(new_array);         //set new queue
            setIHead(0);                 //update new head index
            setITail(j);                 //override new tail
        }else                //if enough space in the queue
            setIHead(h);     //update head index
        setCount(c);         //update queue size/counter
        return e;            //return value that was in the head
    }catch(std::underflow_error e){   //handled exception
        Type exit;
        std::cout << e.what() << std::endl;
        return exit;
    }
}

//clear() will reset the queue to its original values
void queue::clear(){
    if(!empty()){ //if queue is not empty
        delete [] getArray();
        setArraySize(getInitialSize());
        setArray(new Type[getArraySize()]);
        setCount(0);
        setIHead(-1);
        setITail(-1);
    }
}

#endif /* QUEUE_H */
