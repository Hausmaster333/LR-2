#include <stdexcept>
#include "sequence.h"
#include "dynamic_array.h"
#include "linked_list.h"

template <class T>
ArraySequence<T>::ArraySequence() : count(0) {
    array = new DynamicArray<T>();
}

template <class T>
ArraySequence<T>::ArraySequence(const T* items, int count) : count(count) {
    array = new DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& other) : count(other.get_size()) {
    array = new DynamicArray<T>(other);
}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) : count(other.count) {
    array = new DynamicArray<T>(*other.array);
}

template <class T>
const T& ArraySequence<T>::get_first() const {
    if (count == 0) throw std::out_of_range("Sequence is empty\n");

    return array->get(0);
}

template <class T>
const T& ArraySequence<T>::get_last() const {
    if (count == 0) throw std::out_of_range("Sequence is empty\n");

    int last_index = get_count() - 1;
    return array->get(last_index);
}

template <class T>
const T& ArraySequence<T>::get(int index) const {
    if (count == 0) throw std::out_of_range("Sequence is empty\n");

    return array->get(index);
}

template <class T>
int ArraySequence<T>::get_count() const {
    return count;
}

template <class T>
Sequence<T>* ArraySequence<T>::get_sub_sequence(int start, int end) {
    if (count == 0) throw std::out_of_range("Sequence is empty\n");

    if (start < 0 || end < 0 || start >= count || end >= count || start > end) throw std::out_of_range("Index out of range\n");

    int new_count = end - start + 1;
    T* items = new T[new_count];

    for (int i = 0; i < new_count; i++) {
        items[i] = array->get(start + i);
    }

    ArraySequence<T>* sub_array = EmptyClone();
    delete sub_array->array;
    sub_array->array = new DynamicArray<T>(items, new_count);
    sub_array->count = new_count;

    delete[] items;

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
Sequence<T>* ArraySequence<T>::concat(const Sequence<T>* other) {
    if (other == nullptr) {
        throw std::invalid_argument("Cannot concat with nullptr\n");
    }

    int new_count = count + other->get_count();
    T* items = new T[new_count];

    for (int i = 0; i < count; i++) {
        items[i] = array->get(i);
    }

    for (int i = 0; i < other->get_count(); i++) {
        items[count + i] = other->get(i);
    }

    ArraySequence<T>* concat_arr = EmptyClone();
    delete concat_arr->array;
    concat_arr->array = new DynamicArray<T>(items, new_count);
    concat_arr->count = new_count;

    delete[] items;

    return concat_arr;
}

template <class T>
Sequence<T>* ArraySequence<T>::map(T (*func)(const T& elem)) {
    T* items = new T[count];

    for (int i = 0; i < count; i++) {
        T mapped_elem = func(get(i));
        items[i] = mapped_elem;
    }

    ArraySequence<T>* mapped_arr = EmptyClone();
    
    delete mapped_arr->array;
    mapped_arr->array = new DynamicArray<T>(items, count);
    mapped_arr->count = count;

    return mapped_arr;
}

template <class T>
Sequence<T>* ArraySequence<T>::where(bool (*predicate)(const T& elem)) {
    T* items = new T[count];
    int new_count = 0;

    for (int i = 0; i < get_count(); i++) {
        T current_elem = get(i);

        if (predicate(current_elem)) {
            items[new_count] = current_elem;
            new_count++;
        }
    }

    ArraySequence<T>* where_arr = EmptyClone();

    delete where_arr->array;
    where_arr->array = new DynamicArray<T>(items, new_count);
    where_arr->count = new_count;

    delete[] items;

    return where_arr;
}

template <class T>
T ArraySequence<T>::reduce(T (*func)(const T& first_elem, const T& second_elem), const T& initial_elem) {
    T reduced_elem = initial_elem;

    for (int i = 0; i < get_count(); i++) {
        reduced_elem = func(get(i), reduced_elem);
    }

    return reduced_elem;
}
// ==================================================

template <class T>
ListSequence<T>::ListSequence() {
    list = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(const T* items, int count) {
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
const T& ListSequence<T>::get_first() const {
    return list->get_first();
}

template <class T>
const T& ListSequence<T>::get_last() const {
    return list->get_last();
}

template <class T>
const T& ListSequence<T>::get(int index) const {
    return list->get(index);
}

template <class T>
int ListSequence<T>::get_count() const {
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
Sequence<T>* ListSequence<T>::concat(const Sequence<T>* other) {
    if (other == nullptr) {
        throw std::invalid_argument("Cannot concat with nullptr\n");
    }

    ListSequence<T>* concat_list = Instance();

    for (int i = 0; i < other->get_count(); i++) {
        concat_list->append(other->get(i));
    }

    return concat_list;
}

template <class T>
Sequence<T>* ListSequence<T>::map(T (*func)(const T& elem)) {
    ListSequence<T>* mapped_list = EmptyClone();

    for (auto current = start(); current != end(); ++current) {
        T current_elem = *current;
        T mapped_elem = func(current_elem);
        mapped_list->append(mapped_elem);
    }

    return mapped_list;
}

template <class T>
Sequence<T>* ListSequence<T>::where(bool (*predicate)(const T& elem)) {
    ListSequence<T>* where_list = EmptyClone();

    for (auto current = start(); current != end(); ++current) {
        T current_elem = *current;

        if (predicate(current_elem)) {
            where_list->append(current_elem);
        }
    }

    return where_list;
}

template <class T>
T ListSequence<T>::reduce(T (*func)(const T& first_elem, const T& second_elem), const T& initial_elem) {
    T reduced_elem = initial_elem;

    for (auto current = start(); current != end(); ++current) {
        T current_elem = *current;
        reduced_elem = func(current_elem, reduced_elem);
    }

    return reduced_elem;
}

