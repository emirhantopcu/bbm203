//
// Created by emire on 15.12.2020.
//

#ifndef ASSIGNMENT3_STACK_H
#define ASSIGNMENT3_STACK_H


/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);

*/
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Stack {
public:
    Stack(){

    }
    ~Stack(){

    }
    bool isEmpty() const{
        if (_size == 0){
            return true;
        }
        else{
            return false;
        }
    }
    int size() const{
        int counter = 0;
        ListNode* _search = _head;
        while (_search != nullptr){
            _search = _search->next;
            counter++;
        }
        return counter;
    }

    //Push: Place item on top of the stack
    void push(const T& newItem){
        if (isEmpty()){
            _head = new ListNode;
            _head->item = newItem;
            _head->next = nullptr;
            _size++;
        }
        else{
            ListNode* _temp;
            _temp = _head;
            _head = new ListNode;
            _head->item = newItem;
            _head->next = _temp;
            _size++;
        }
    }
    //Top: Take a look at the topmost item without removing it
    void getTop(T& stackTop) const{
        if (!isEmpty()){
            stackTop = _head->item;
        }
    }
    //Pop: Remove item from the top of the stack
    void pop(){
        if (size() == 1){
            _head = nullptr;
        }else if(size() > 1){
            ListNode* _temp;
            _temp = _head;
            _head = _head->next;
            delete _temp;
        }
        _size--;
    }
    vector<T> listElements(){
        ListNode* _temp = _head;
        vector<T> output;
        while (_temp != nullptr){
            output.push_back(_temp->item);
            _temp = _temp->next;
        }
        return output;
    }
private:
    struct ListNode {
        T item;
        ListNode* next;
    };
    ListNode* _head = nullptr;
    int _size = 0;
};


#endif //ASSIGNMENT3_STACK_H
