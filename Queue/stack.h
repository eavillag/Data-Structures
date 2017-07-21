#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <iomanip>
#include <stdexcept>

typedef std::string Type;

// Stack class stores elements in a dynamically allocated and sized array.
// It pushes elements to the top of the stack and pops them from the top
class stack
{
private:
    Type *array;
    int count;
    int initialSize;
    int arraySize;
public:
    stack(int size = 15);
    stack(const stack &);
    virtual ~stack();

    // ACCESSORS
    Type top() const;
    int size() const;
    bool empty() const;
    int capacity() const;
    void display();

    // MUTATORS
    void push(Type const &);
    Type pop();
    void clear();

    // GETTERS/SETTERS
    Type* GetArray() const;
    void SetArray(Type *);
    int GetCount() const;
    void SetCount(const int &);
    int GetInitialSize() const;
    void SetInitialSize(const int &);
    int GetArraySize() const;
    void SetArraySize(const int &);
};

// class constructor, takes default size of 15
stack::stack(int size)
{
    try{
        if(size <= 0)
            size = 1;
        SetArray(new Type[size]);
        SetInitialSize(size);
        SetArraySize(size);
        SetCount(0);
    }catch(const std::exception &e){
        throw(e.what());
    }
}

// copy constructor
stack::stack(const stack& temp){}

// default destructor
stack::~stack(){}

// ACCESSORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Type stack::top() const
{
    try{
        if(empty())
            throw std::underflow_error("UnderFlow error. Empty stack");
        else
            return GetArray()[GetCount()- 1];
    }catch( std::underflow_error e)
    {
        Type ret;
        std::cout << "Exception: " << e.what() << std::endl;
        return ret;
    }
}

int stack::size() const
{
    try{
        return GetCount();
    }catch(const std::exception &e){
        throw(e.what());
    }
}

// returns whether or not the stack is empty
bool stack::empty() const
{
    try{
        return GetCount() == 0;
    }catch(const std::exception &e){
        throw(e.what());
    }
}

// returns current capacity of the array
int stack::capacity() const
{
    try{
        return GetArraySize();
    }catch(const std::exception &e){
        throw(e.what());
    }
}

void stack::display()
{
    try{
        if(empty())
            std::cout << "Stack is empty." << std::endl;
        else
        {
            for(int i=GetCount(); i > 0; i--)
                std::cout << "Element " << GetCount() - i + 1 << std::setw(10) << GetArray()[i - 1] << std::endl;
        }
    }catch(const std::exception &e){
        throw(e.what());
    }
}
// END ACCESSORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// GETTERS/SETTERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Type* stack::GetArray() const
{
    return this->array;
}

void stack::SetArray(Type *arr)
{
    this->array = arr;
}

int stack::GetCount() const
{
    return this->count;
}

void stack::SetCount(const int &num)
{
    this->count = num;
}

int stack::GetInitialSize() const
{
    return this->initialSize;
}

void stack::SetInitialSize(const int &size)
{
    this->initialSize = size;
}

int stack::GetArraySize() const
{
    return this->arraySize;
}

void stack::SetArraySize(const int &size)
{
    this->arraySize = size;
}
// END GETTERS/SETTERS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// MUTATORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// pushes element to top of the stack
void stack::push(const Type &data)
{
    try{
        int count = GetCount(), size = GetArraySize();                  // Check if array is full
        if(count == size)
        {
            SetArraySize(size*2);                                       // Double size of array
            Type* resize = new Type[GetArraySize()],  *orig = GetArray();

            for(int i = 0; i < count; i++)                              // Copy original elements to new array
                resize[i] = orig[i];

            delete[] orig;                                              // Deallocate original array
            SetArray(resize);                                           // Set new, resized array
        }
        GetArray()[count] = data;                                       // Add new element
        SetCount(++count);                                              // Increase counter
    }catch(const std::exception &e){
        throw(e.what());
    }
}

// pops element from the top of the stack
Type stack::pop()
{
    try{
        if(empty())
            throw std::underflow_error("UnderFlow error. Empty stack");
        else
        {
            int count = GetCount(), size = GetArraySize();
            Type popped = top();
            SetCount(count - 1);

            if(count == (size/4) && (size/2) > GetInitialSize())        // Check if array is 1/4 full and size is greater thn initialSize
            {
                SetArraySize(size/2);                                   // Half size of array
                Type *resize = new Type[GetArraySize()], *orig = GetArray();

                for(int i = 0; i < GetCount(); i++)                     // Copy original elemnts to array
                    resize[i] = orig[i];

                delete[] orig;                                          // Deallocate original array
                SetArray(resize);                                       // Set new, resized array
            }

            return popped;
        }
    }catch(const std::exception &e){
        Type ret;
        std::cout << "Exception: " << e.what() << std::endl;
        return ret;
    }
}

void stack::clear()
{
    try{
        if(!empty())                                                    // Check if stack is empty
        {
            delete[] GetArray();                                        // Deallocate original array
            SetArray(new Type[GetInitialSize()]);                       // Allocate memory for new array at initialSize
            SetCount(0);                                                // Reset count
            SetArraySize(GetInitialSize());                             // Reset arraySize
        }
        else
            std::cout << "Stack is already empty" << std::endl;
    }catch(const std::exception &e){
        throw(e.what());
    }
}
// END MUTATORS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#endif
