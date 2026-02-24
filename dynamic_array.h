#ifndef ARRAY_H
#define ARRAY_H

template <class T>
class DynamicArray {
    private:
        T* data;
        int size;

    public:
        DynamicArray(int size);
        DynamicArray(T* items, int count);
        DynamicArray(const DynamicArray<T>& other);

        T get(int index);

        int get_size();

        void set(int index, T value);

        void resize(int newSize);

        ~DynamicArray();
};

#include "dynamic_array.tpp"

#endif