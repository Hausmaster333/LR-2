#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <class T>
class LinkedList {
    private:
        struct Node {
            T data;
            Node* next;
        };

        Node* head;
        Node* tail;
        int length;
    public:
        LinkedList();
        LinkedList(const T* items, int count);
        LinkedList(const LinkedList<T>& other);

        LinkedList<T>& operator=(const LinkedList<T>& other);

        const T& get_first() const;
        const T& get_last() const;
        const T& get(int index) const; // Лучше использовать Iterator
        int get_length() const;

        LinkedList<T>* get_sub_list(int start, int end);

        void append(T item); // В конец
        void prepend(T item); // В начало
        void insert_at(T item, int index);

        LinkedList<T>* concat(const LinkedList<T>* other);

        ~LinkedList();

        class Iterator {
            private:
                Node* current;
            public:
                Iterator(Node* node) : current(node) {}

                const T& operator*() const { return current->data; }

                Iterator& operator++() {
                    current = current->next;
                    return *this;
                }

                bool operator!=(const Iterator& other) const {
                    return current != other.current;
                }
        };

        Iterator start() const { return Iterator(head); }
        Iterator end() const { return Iterator(nullptr); }
};

#include "linked_list.tpp"

#endif