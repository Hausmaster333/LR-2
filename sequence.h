#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "dynamic_array.h"
#include "linked_list.h"

template <class T>
class Sequence {
    public:
        virtual T get_first() const = 0;
        virtual T get_last() const = 0;
        virtual T get(int index) const = 0; // Итератор, убрать get в аррей. Сделать интератор + передавать константные ссылки 
        virtual int get_count() = 0;

        virtual Sequence<T>* get_sub_sequence(int start, int end) = 0;

        virtual Sequence<T>* append(T item) = 0;
        virtual Sequence<T>* prepend(T item) = 0;
        virtual Sequence<T>* insert_at(T item, int index) = 0;
        virtual Sequence<T>* concat(Sequence<T>* other) = 0;

        virtual ~Sequence() {}
};

template <class T>
class ArraySequence : public Sequence<T> {
    protected:    
        DynamicArray<T>* array;
        int count;
    public:
        ArraySequence();
        ArraySequence(const T* items, int count);
        ArraySequence(const DynamicArray<T>& other);
        ArraySequence(const ArraySequence<T>& other);

        virtual ArraySequence<T>* Instance() = 0;
        virtual ArraySequence<T>* EmptyClone() = 0;

        T get_first() override;
        T get_last() override;
        T get(int index) override;
        int get_count() override;

        Sequence<T>* get_sub_sequence(int start, int end) override;

        Sequence<T>* append(T item) override;
        Sequence<T>* prepend(T item) override;
        Sequence<T>* insert_at(T item, int index) override;
        Sequence<T>* concat(Sequence<T>* other) override;

        ~ArraySequence() override {
            delete array;
        }
};

template <class T>
class ListSequence : public Sequence<T> {
    protected:    
        LinkedList<T>* list;
    public:
        ListSequence();
        ListSequence(T* items, int count);
        ListSequence(const LinkedList<T>& other);
        ListSequence(const ListSequence<T>& other);

        virtual ArraySequence<T>* Instance() = 0;
        virtual ListSequence<T>* EmptyClone() = 0;

        T get_first() override;
        T get_last() override;
        T get(int index) override;
        int get_count() override;

        Sequence<T>* get_sub_sequence(int start, int end) override;

        Sequence<T>* append(T item) override;
        Sequence<T>* prepend(T item) override;
        Sequence<T>* insert_at(T item, int index) override;
        Sequence<T>* concat(Sequence<T>* other) override;
    
        ~ListSequence() override {
            delete list;
        }
};

template <class T>
class MutableArraySequence : public ArraySequence<T> {
    protected:        
        ArraySequence<T>* Instance() override {
            return this; // Возвращаем исходный объект
        };

        ArraySequence<T>* EmptyClone() override {
            return new MutableArraySequence<T>();
        };

    public:
        MutableArraySequence() : ArraySequence<T>() {};
        MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {};
        MutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {};
        MutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {};
};

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
    protected:
        ArraySequence<T>* Instance() override {
            return new ImmutableArraySequence<T>(*this); // Возвращаем копию(получаем объект -> отдаем по ссылке)
        };

        ArraySequence<T>* EmptyClone() override {
            return new ImmutableArraySequence<T>();
        };

    public:
        ImmutableArraySequence() : ArraySequence<T>() {};
        ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {};
        ImmutableArraySequence(const DynamicArray<T>& other) : ArraySequence<T>(other) {};
        ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {};
};

template <class T>
class MutableListSequence : public ListSequence<T> {
    protected:        
        ListSequence<T>* Instance() override {
            return this; // Возвращаем исходный объект
        };

        ListSequence<T>* EmptyClone() override {
            return new MutableListSequence<T>();
        };

    public:
        MutableListSequence() : ListSequence<T>() {};
        MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {};
        MutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {};
        MutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {};
};

template <class T>
class ImmutableListSequence : public ListSequence<T> {
    protected:
        ListSequence<T>* Instance() override {
            return new ImmutableListSequence<T>(*this); // Возвращаем копию(получаем объект -> отдаем по ссылке)
        };

        ListSequence<T>* EmptyClone() override {
            return new ImmutableListSequence<T>();
        };
        
    public:
        ImmutableListSequence() : ListSequence<T>() {};
        ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {};
        ImmutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {};
        ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {};
};

#include "sequence.tpp"

#endif