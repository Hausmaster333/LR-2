#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "dynamic_array.h"
#include "linked_list.h"
#include "option.h"

template <class T>
class Sequence {
    public:
        virtual const T& get_first() const = 0; // const T& ссылка, чтобы не копировать объект, а просто const запрещает менять значение через эту ссылку
        virtual const T& get_last() const = 0;
        virtual const T& get(int index) const = 0;

        virtual Option<T> try_get_first() const = 0;
        virtual Option<T> try_get_last() const = 0;
        virtual Option<T> try_get(int index) const = 0;

        virtual int get_count() const = 0;

        virtual Sequence<T>* get_sub_sequence(int start, int end) = 0;

        virtual Sequence<T>* append(T item) = 0;
        virtual Sequence<T>* prepend(T item) = 0;
        virtual Sequence<T>* insert_at(T item, int index) = 0;
        virtual Sequence<T>* concat(const Sequence<T>* other) = 0;

        virtual Sequence<T>* map(T (*func)(const T& elem)) = 0;
        virtual Sequence<T>* where(bool (*predicate)(const T& elem)) = 0;
        virtual T reduce(T (*func)(const T& first_elem, const T& second_elem), const T& initial_elem) = 0;

        virtual ~Sequence() {}
};

template <class T>
class ArraySequence : public Sequence<T> {
    protected:    
        DynamicArray<T>* array;
        int count;
    public:
        ArraySequence();
        ArraySequence(const T* items, int count); // const items
        ArraySequence(const DynamicArray<T>& other);
        ArraySequence(const ArraySequence<T>& other);

        virtual ArraySequence<T>* Instance() = 0;
        virtual ArraySequence<T>* EmptyClone() = 0;

        const T& get_first() const override;
        const T& get_last() const override;
        const T& get(int index) const override;

        Option<T> try_get_first() const override;
        Option<T> try_get_last() const override;
        Option<T> try_get(int index) const override;

        int get_count() const override;

        Sequence<T>* get_sub_sequence(int start, int end) override;

        Sequence<T>* append(T item) override;
        Sequence<T>* prepend(T item) override;
        Sequence<T>* insert_at(T item, int index) override;
        Sequence<T>* concat(const Sequence<T>* other) override;

        Sequence<T>* map(T (*func)(const T& elem)) override;
        Sequence<T>* where(bool (*predicate)(const T& elem)) override;
        T reduce(T (*func)(const T& first_elem, const T& second_elem), const T& initial_elem) override;

        // typename DynamicArray<T>::Iterator start() const { return array->start(); }
        // typename DynamicArray<T>::Iterator end() const { return array->end(); }

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
        ListSequence(const T* items, int count);
        ListSequence(const LinkedList<T>& other);
        ListSequence(const ListSequence<T>& other);

        virtual ListSequence<T>* Instance() = 0;
        virtual ListSequence<T>* EmptyClone() = 0;

        const T& get_first() const override;
        const T& get_last() const override;
        const T& get(int index) const override;

        Option<T> try_get_first() const override;
        Option<T> try_get_last() const override;
        Option<T> try_get(int index) const override;

        int get_count() const override;

        Sequence<T>* get_sub_sequence(int start, int end) override;

        Sequence<T>* append(T item) override;
        Sequence<T>* prepend(T item) override;
        Sequence<T>* insert_at(T item, int index) override;
        Sequence<T>* concat(const Sequence<T>* other) override;

        Sequence<T>* map(T (*func)(const T& elem)) override;
        Sequence<T>* where(bool (*predicate)(const T& elem)) override;
        T reduce(T (*func)(const T& first_elem, const T& second_elem), const T& initial_elem) override;

        typename LinkedList<T>::Iterator start() const { return list->start(); }
        typename LinkedList<T>::Iterator end() const { return list->end(); }

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
        MutableArraySequence(const T* items, int count) : ArraySequence<T>(items, count) {};
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
        ImmutableArraySequence(const T* items, int count) : ArraySequence<T>(items, count) {};
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
        MutableListSequence(const T* items, int count) : ListSequence<T>(items, count) {};
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
        ImmutableListSequence(const T* items, int count) : ListSequence<T>(items, count) {};
        ImmutableListSequence(const LinkedList<T>& other) : ListSequence<T>(other) {};
        ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {};
};

class Bit {
    private:
        bool value;
    public:
        Bit() : value(false) {}
        Bit(bool val) : value(val) {}
        Bit(int val) : value(val != 0) {}

        bool get() const { return value; }

        Bit operator&(const Bit& other) const { return Bit(value && other.value); } // Логическое И
        Bit operator|(const Bit& other) const { return Bit(value || other.value); } // Логическое ИЛИ
        Bit operator^(const Bit& other) const { return Bit(value != other.value); } // Логическое XOR
        Bit operator~() const { return Bit(!value); } // Логическое НЕ

        bool operator==(const Bit& other) const { return value == other.value; }
        bool operator!=(const Bit& other) const { return value != other.value; }
};

class BitSequence {
    private:
        Sequence<Bit>* seq;
    public:
        BitSequence(Sequence<Bit>* sequence) : seq(sequence) {} // Передаем new Mutable[Immutable]Array[List]Sequence<Bit>()

        void append(const Bit& item) { seq->append(item); }
        const Bit& get(int index) const { return seq->get(index); }
        int get_count() const { return seq->get_count(); }

        BitSequence* bit_and(const BitSequence& other) const; // И
        BitSequence* bit_or(const BitSequence& other) const; // ИЛИ
        BitSequence* bit_xor(const BitSequence& other) const; // XOR
        BitSequence* bit_not() const; // НЕ

        ~BitSequence() {
            delete seq;
        }
};

#include "sequence.tpp"

#endif