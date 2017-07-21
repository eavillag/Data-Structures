//Authors: Eduardo Villa
//         Brooks Olney
// This program will prompt the user to create either a stack or a queue
// and give them a list of options to execute on the object created

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "stack.h"
#include "queue.h"

using namespace std;

typedef std::string Type;

// function headers
void showMenu();
int executeActionStack(int,stack *&stackObject);
int executeActionQueue(int, queue *&queueObject);

int main(int argc, char** argv) {
    char c;
    int op,exit=0;
    cout << "Enter 's' or 'q'" <<endl;
    cin >> c;
    if(c!= 's' && c!='q')
        cout << "Wrong option" << endl;
    else{
        if(c == 's')
        {
            stack *structure = new stack();          // Allocate memory for new stack object
            showMenu();
            cout << "Enter an option" << endl;
            cin >> op;

            exit = executeActionStack(op,structure);
            while(!exit){                            // run through options until user terminates
                cout << "Enter an option: ";
                cin >> op;
                exit = executeActionStack(op,structure);
            }
        }
        else
        {
            queue *structure = new queue();          // Allocate memory for new queue object
            showMenu();
            cout << "Enter an option" << endl;
            cin >> op;

            exit = executeActionQueue(op,structure,c);
            while(!exit){                            // run through options until user terminates
                cout << "Enter an option: ";
                cin >> op;
                exit = executeActionQueue(op,structure,c);
            }
        }

    }
    return 0;
}

// displays the menu options to the user
void showMenu(){
    cout << "1. Return Capacity" << endl;
    cout << "2. Return Size of data structure" << endl;
    cout << "3. View first item" << endl;
    cout << "4. Insert item" << endl;
    cout << "5. Delete item" << endl;
    cout << "6. Display" << endl;
    cout << "7. Clear" << endl;
    cout << "8. Exit" << endl;
}

// executes the action on the stack that has been selected by the user
int executeActionStack(int op, stack *&stackObject){
    int exit=0;
    Type elem;
    switch(op){
            case 1:
                std::cout << "Capacity of Stack:  " << stackObject->capacity() << std::endl;
                break;
            case 2:
                std::cout << "Size of Stack: " << stackObject->size() << std::endl;
                break;
            case 3:
                std::cout << "Top item: " << stackObject->top() << std::endl;
                break;
            case 4:
                std::cout << "Enter element to push onto Stack: " << std::endl;
                cin >> elem;
                stackObject ->push(elem);
                break;
            case 5:
                std::cout<<"Element popped from Stack: " << stackObject->pop() << std::endl;
                break;
            case 6:
                stackObject->display();
                break;
            case 7:
                stackObject->clear();
                break;
            case 8:
                exit = 1;
                break;
        }
    return exit;
}

// executes the action that has been selected by the user
int executeActionQueue(int op, queue *&queueObject){
    int exit=0;
    Type elem;
    switch(op){
            case 1:
                std::cout << "Capacity of Queue:  " << queueObject->capacity() << std::endl;
                break;
            case 2:
                std::cout << "Size of Queue: " << queueObject->size() << std::endl;
                break;
            case 3:
                std::cout << "Front item: " << queueObject->front() << std::endl;
                break;
            case 4:
                std::cout << "Enter element to enqueue: " << std::endl;
                cin >> elem;
                queueObject ->enqueue(elem);
                break;
            case 5:
                std::cout<<"Element dequeued: " << queueObject->dequeue() << std::endl;
                break;
            case 6:
                queueObject->display();
                break;
            case 7:
                queueObject->clear();
                break;
            case 8:
                exit = 1;
                break;
        }
    return exit;
}
