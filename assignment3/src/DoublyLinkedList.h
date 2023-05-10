//
// Created by emire on 16.12.2020.
//

#ifndef ASSIGNMENT3_DOUBLYLINKEDLIST_H
#define ASSIGNMENT3_DOUBLYLINKEDLIST_H

template<typename T>
class DoublyLinkedList{
public:
    DoublyLinkedList(){

    }
    ~DoublyLinkedList(){

    }
    bool isEmpty() const{
        if (_last == nullptr){
            return true;
        }
        else{
            return false;
        }
    }
    int size() const{
        return _size;
    }
    void append(const T& newItem){
        if (isEmpty()){
            _last = new Node;
            _last->item = newItem;
            _last->next = _last;
            _last->prev = _last;
            _size++;
        }
        else{
            if (size() == 1){
                Node* _temp;
                _temp = _last;
                _last = new Node;
                _last->item = newItem;
                _temp->next = _last;
                _temp->prev = _last;
                _last->next = _temp;
                _last->prev = _temp;
                _size++;
            } else{
                Node* _temp;
                _temp = _last;
                _last = new Node;
                _last->item = newItem;
                _temp->next->prev = _last;
                _last->next = _temp->next;
                _temp->next = _last;
                _last->prev = _temp;
                _size++;
            }
        }
    }
    void remove(int index){
        Node* _search = _last->next;
        for (int i = 0; i < index; ++i) {
            _search = _search->next;
        }
        if (_search == _last){
            _last = _search->prev;
            _last->next = _search->next;
            _search->next->prev = _last;
            _search->next = nullptr;
            _search->prev = nullptr;
            delete _search;
            _size--;
        }else{
            _search->prev->next = _search->next;
            _search->next->prev = _search->prev;
            _search->prev = nullptr;
            _search->next = nullptr;
            _size--;
        }
    }
    T& get(int index) const{
        Node* _search = _last->next;
        for (int i = 0; i < index; ++i) {
            _search = _search->next;
        }
        return _search->item;
    }
private:
    struct Node {
        T item;
        Node *next;
        Node *prev;
    };
    int _size = 0;
    Node* _last = nullptr;
};
#endif //ASSIGNMENT3_DOUBLYLINKEDLIST_H