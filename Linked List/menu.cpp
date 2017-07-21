//Authors: Eduado Villa
//         Brooks Olney
//This program will blah blah blah

#include <cstdlib>
#include <iostream>
#include <iomanip>

#include "DoubleLinkedList.h"
#include "CyclicLinkedList.h"
#include "List.h"

using namespace std;

typedef int Type;

void showMenu();
int executeAction(int,List<Type> *&,char c);
List<Type>* createList(char c);

int main(int argc, char** argv) {
    char c;
    int op,exit=0;
    cout << "Enter 's' or 'd'" <<endl;
    cin >> c;
    if(c!= 'd' && c!='s')
        cout << "Wrong option" << endl;
    else{
        List<Type>* linkedList;
        showMenu();
        cout << "Enter an option" << endl;
        cin >> op;
        
        while(op != 1){
            cout << "Need to create a list first." << endl;
            cout << "Enter an option: ";
            cin >> op;
        }
        exit = executeAction(op,linkedList,c);           
        while(!exit){
            cout << "Enter an option: ";
            cin >> op;
            exit = executeAction(op,linkedList,c);           
        }
    }    
    return 0;
}

void showMenu(){
    cout << "1. Create List" << endl;
    cout << "2. Count number of Items" << endl;
    cout << "3. Retrieve first item" << endl;
    cout << "4. Retrieve last item" << endl;
    cout << "5. Count instances of an item" << endl;
    cout << "6. Push front" << endl;
    cout << "7. Push back" << endl;
    cout << "8. Pop front" << endl;
    cout << "9. Pop back" << endl;
    cout << "10. Delete instance(s) of an item" << endl;
    cout << "11. Print list" << endl;
    cout << "12. Exit" << endl;
}

int executeAction(int op, List<Type> *&linkedList,char c){
    int exit=0;
    Type elem;
    switch(op){
            case 1:
                linkedList=createList(c);
                break;
            case 2:
                std::cout << "# of items: " <<setw(4) <<linkedList->GetSize() << " " <<endl;
                break;
            case 3:
                if(linkedList->GetSize()>0)
                    std::cout << "First Element: " <<setw(4) << linkedList->GetHead()->GetData()<<endl <<" "<<endl;
                else
                    std::cout << "List Empty" << endl;
                break;
            case 4:
                if(linkedList->GetSize()>0)
                    std::cout << "Last Element: " <<setw(4) << linkedList->GetTail()->GetData()<<endl <<" "<<endl;
                else
                    std::cout << "List Empty" << endl;
                break;
            case 5:
                std::cout<<"Value to search for? :";
                std::cin >> elem;
                std::cout << "Element: " <<setw(4)<<elem<<" appears "<<linkedList->count(elem)<<endl;
                break;
            case 6:
                std::cout << "Element to push in front? :";
                std::cin >> elem;
                linkedList->push_front(elem);
                break;
            case 7:
                std::cout << "Element to push at the back? :";
                std::cin >> elem;
                linkedList->push_back(elem);
                break;
            case 8:
                std::cout << "pop_front() : " <<setw(4) << linkedList->pop_front()<< " "<<endl;
                break;
            case 9:
                std::cout << "pop_back() : " <<setw(4) << linkedList->pop_back()<<" "<<endl;
                break;
            case 10:
                std::cout<<"Value(s) to delete? :";
                std::cin >> elem;
                linkedList->erase(elem);
                break;
            case 11:
                linkedList->printList();
                break;
            case 12:
                exit = 1;
                break;
        }
    return exit;
}

List<Type>* createList(char c){
    List<Type> *newList;
    if(c=='d')
         newList=new DoubleLinkedList<Type>();
    if(c=='s')
         newList=new CyclicLinkedList<Type>();
    return newList;
}