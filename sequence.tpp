#include <stdexcept>
#include "sequence.h"
#include "dynamic_array.h"
#include "linked_list.h"

template <class T>
ArraySequence<T>::ArraySequence() : count(0) {
    array = new DynamicArray<T>();
}

template <class T>
ArraySequence<T>::ArraySequence(T* items, int count) : count(count) {
    array = new DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& other) : count(other.size) {
    array = new DynamicArray<T>(other);
}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) : count(other.count) {
    array = new DynamicArray<T>(*other.array);
}

template <class T>
T ArraySequence<T>::get_first() {
    if (count == 0) throw std::out_of_range("Sequence is empty\n");

    return array->get(0);
}

template <class T>
T ArraySequence<T>::get_last() {
    if (count == 0) throw std::out_of_range("Sequence is empty\n");

    int last_index = get_count() - 1;
    return array->get(last_index);
}

template <class T>
T ArraySequence<T>::get(int index) {
    if (count == 0) throw std::out_of_range("Sequence is empty\n");

    return array->get(index);
}

template <class T>
int ArraySequence<T>::get_count() {
    return count;
}

template <class T>
Sequence<T>* ArraySequence<T>::get_sub_sequence(int start, int end) {
    if (count == 0) throw std::out_of_range("Sequence is empty\n");

    if (start < 0 || end < 0 || start >= count || end >= count || start > end) throw std::out_of_range("Index out of range\n");

    ArraySequence<T>* sub_array = EmptyClone();

    for (int i = start; i < end; i++) {
        sub_array->append(array->get(i));
    }

    return sub_array;
}

template <class T>
Sequence<T>* ArraySequence<T>::append(T item) {
    ArraySequence<T>* inst = Instance();

    int size = inst->array->get_size();

    if (inst->count >= size) {
        int new_size = (size == 0) ? 4 : size * 2;
        inst->array->resize(new_size);
    }

    inst->array->set(inst->count, item);
    inst->count++;

    return inst;
}

template <class T>
Sequence<T>* ArraySequence<T>::prepend(T item) {
    ArraySequence<T>* inst = Instance();

    int size = inst->array->get_size();

    if (inst->count >= size) {
        int new_size = (size == 0) ? 4 : size * 2;
        inst->array->resize(new_size);
    }

    for (int i = inst->count; i > 0; i--) {
        inst->array->set(i, inst->array->get(i - 1));
    }

    inst->array->set(0, item);
    inst->count++;
    return inst;
}

template <class T>
Sequence<T>* ArraySequence<T>::insert_at(T item, int index) {

    ArraySequence<T>* inst = Instance();

    if (index < 0 || index > inst->count) {
        throw std::out_of_range("Index out of range\n");
    }

    int size = inst->array->get_size();

    if (inst->count >= size) {
        int new_size = (size == 0) ? 4 : size * 2;
        inst->array->resize(new_size);
    }

    for (int i = inst->count; i > index; i--) {
        inst->array->set(i, inst->array->get(i - 1));
    }

    inst->array->set(index, item);
    inst->count++;
    return inst;
}

template <class T>
Sequence<T>* ArraySequence<T>::concat(Sequence<T>* other) {
    if (other == nullptr) {
        throw std::invalid_argument("Cannot concat with nullptr\n");
    }

    ArraySequence<T>* concat_arr = Instance();

    for (int i = 0; i < other->get_count(); i++) {
        concat_arr->append(other->get(i));
    }

    return concat_arr;
}

// ==================================================

template <class T>
ListSequence<T>::ListSequence() {
    list = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(T* items, int count) {
    list = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence(const LinkedList<T>& other) {
    list = new LinkedList<T>(other);
}

template <class T>
ListSequence<T>::ListSequence(const ListSequence<T>& other) {
    list = new LinkedList<T>(*other.list);
}

template <class T>
T ListSequence<T>::get_first() {
    return list->get_first();
}

template <class T>
T ListSequence<T>::get_last() {
    return list->get_last();
}

template <class T>
T ListSequence<T>::get(int index) {
    return list->get(index);
}

template <class T>
int ListSequence<T>::get_count() {
    return list->get_length();
}

template <class T>
Sequence<T>* ListSequence<T>::get_sub_sequence(int start, int end) {
    if (start < 0 || end < 0 || start >= get_count() || end >= get_count() || start > end) {
        throw std::out_of_range("Index out of range");
    }

    ListSequence<T>* sub_list = EmptyClone();

    for (int i = start; i <= end; i++) {
        sub_list->append(list->get(i));
    }

    return sub_list;
}

template <class T>
Sequence<T>* ListSequence<T>::append(T item) {
    ListSequence<T>* inst = Instance();

    inst->list->append(item);
    return inst;
}

template <class T>
Sequence<T>* ListSequence<T>::prepend(T item) {
    ListSequence<T>* inst = Instance();

    inst->list->prepend(item);
    return inst;
}

template <class T>
Sequence<T>* ListSequence<T>::insert_at(T item, int index) {
    ListSequence<T>* inst = Instance();

    inst->list->insert_at(item, index);
    return inst;
}

template <class T>
Sequence<T>* ListSequence<T>::concat(Sequence<T>* other) {
    if (other == nullptr) {
        throw std::invalid_argument("Cannot concat with nullptr\n");
    }

    ListSequence<T>* concat_list = Instance();

    for (int i = 0; i < other->get_count(); i++) {
        concat_list->append(other->get(i));
    }

    return concat_list;
}


