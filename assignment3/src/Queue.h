//
// Created by emire on 15.12.2020.
//

#ifndef ASSIGNMENT3_QUEUE_H
#define ASSIGNMENT3_QUEUE_H


/*Function templates are special functions that can operate
with generic types. This allows us to create a function
template whose functionality can be adapted to more than
one type or class without repeating the entire code for each type.*/

/*To use this function template we use the following format for the function call:

function_name <type> (parameters);
*/

#include <vector>


template<typename T>
class Queue {
public:
    Queue(){

    }
    ~Queue(){

    }
    bool isEmpty() const{
        if (_lastNode == nullptr){
            return true;
        } else{
            return false;
        }
    }
    int size() const{
        return _size;
    }
    //Enqueue: Items are added to the back of the queue
    void enqueue(const T& newItem){
        if (isEmpty()){
            _lastNode = new QueueNode;
            _lastNode->item = newItem;
            _lastNode->next = _lastNode;
            _size++;
        }else{
            QueueNode* _temp;
            _temp = _lastNode;
            _lastNode = new QueueNode;
            _lastNode->item = newItem;
            _lastNode->next = _temp->next;
            _temp->next = _lastNode;
            _size++;
        }
    }
    //Dequeue: Items are removed from the front of the queue
    void dequeue(){
        if (size() == 1){
            _lastNode = nullptr;
        }else{
            QueueNode* _firstNode = _lastNode->next;
            _lastNode->next = _firstNode->next;
            delete _firstNode;
        }
        _size--;
    }
    //Get Front: Take a look at the first item
    void getFront(T& queueTop) const{
        if (!isEmpty()){
            queueTop = _lastNode->next->item;
        }
    }
    vector<T> listElements(){
        vector<T> output;
        if (size() != 0){
            QueueNode* _temp = _lastNode->next;
            for (int i = 0; i < size(); ++i) {
                output.push_back(_temp->item);
                _temp = _temp->next;
            }
        }
        return output;
    }
private:
    struct QueueNode {
        T item;
        QueueNode *next;
    };
    int _size = 0;
    /* to avoid the traversal to the last node,
     an additional pointer to the last node is defined*/
    QueueNode *_lastNode = nullptr;
};


#endif //ASSIGNMENT3_QUEUE_H
