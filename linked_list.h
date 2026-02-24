#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <class T>
struct Node {
    T data;
    Node* next;
};

template <class T>
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
        int length;
    
    public:
        LinkedList(T* items, int count);
        LinkedList();
        LinkedList(const LinkedList<T>& other);

        T get_first();
        T get_last();
        T get(int index);

        int get_length();

        LinkedList<T>* get_sub_list(int start, int end);

        void append(T item); // В конец
        void prepend(T item); // В начало
        void insert_at(T item, int index);

        LinkedList<T>* concat(LinkedList<T>* other);

        ~LinkedList();
};

#include "linked_list.tpp"

#endif