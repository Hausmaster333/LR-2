#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "dynamic_array.h"
#include "linked_list.h"

template <class T>
class Sequence {
    public:
        virtual T get_first() = 0;
        virtual T get_last() = 0;
        virtual T get(int index) = 0;
        virtual int get_length() = 0;

        virtual Sequence<T>* get_sub_sequence(int start, int end) = 0;

        virtual Sequence<T>* append(T item) = 0;
        virtual Sequence<T>* prepend(T item) = 0;
        virtual Sequence<T>* insert_at(T item, int index) = 0;
        virtual Sequence<T>* concat(Sequence<T>* other) = 0;

        virtual ~Sequence() {}
};

template <class T>
class ArraySequence : public Sequence<T> {
    private:    
        DynamicArray<T>* items;
    public:
        ArraySequence();
        ArraySequence(T* items, int count);
        ArraySequence(const DynamicArray<T>& other);
        ArraySequence(const ArraySequence<T>& other);

        T get_first() override;
        T get_last() override;
        T get(int index) override;
        int get_length() override;

        Sequence<T>* get_sub_sequence(int start, int end) override;

        Sequence<T>* append(T item) override;
        Sequence<T>* prepend(T item) override;
        Sequence<T>* insert_at(T item, int index) override;
        Sequence<T>* concat(Sequence<T>* other) override;

        ~ArraySequence() {
            delete items;
        }
};

template <class T>
class ListSequence : public Sequence<T> {
    private:    
        LinkedList<T>* items;
    public:
        ListSequence();
        ListSequence(T* items, int count);
        ListSequence(const LinkedList<T>& other);
        ListSequence(const ListSequence<T>& other);

        T get_first() override;
        T get_last() override;
        T get(int index) override;
        int get_length() override;

        Sequence<T>* get_sub_sequence(int start, int end) override;

        Sequence<T>* append(T item) override;
        Sequence<T>* prepend(T item) override;
        Sequence<T>* insert_at(T item, int index) override;
        Sequence<T>* concat(Sequence<T>* other) override;
    
        ~ListSequence() {
            delete items;
        }
};

#include "sequence.tpp"

#endif