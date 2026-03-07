#ifndef ARRAY_H
#define ARRAY_H

template <class T>
class DynamicArray {
    private:
        T* data;
        int size;
    public:
        DynamicArray();
        DynamicArray(int size);
        DynamicArray(const T* items, int count);
        DynamicArray(const DynamicArray<T>& other);

        DynamicArray<T>& operator=(const DynamicArray<T>& other);

        const T& get(int index) const;

        int get_size() const;

        void set(int index, T value);

        void resize(int newSize);

        ~DynamicArray();

        // class Iterator {
        //     private:
        //         T* current;
        //     public:
        //         Iterator(T* ptr) : current(ptr) {}

        //         const T& operator*() const { return *current; }

        //         Iterator& operator++() {
        //             current++;
        //             return *this;
        //         }

        //         bool operator!=(const Iterator& other) const {
        //             return current != other.current;
        //         }
        // };

        // Iterator start() const { return Iterator(data); }
        // Iterator end() const { return Iterator(data + size); }
            
};

#include "dynamic_array.tpp"

#endif