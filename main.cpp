#include "sequence.h"
#include <iostream>

int main() {
    MutableArraySequence<int> a;
    a.append(1);
    a.append(2);
    std::cout << a.get_first() << std::endl;

    ImmutableArraySequence<int> b;
    Sequence<int>* b2 = b.append(1);
    Sequence<int>* b3 = b2->append(2);
    
    delete b2;  
    delete b3;

    DynamicArray<int> row1(3);
    row1.set(0, 1);
    row1.set(1, 2);
    row1.set(2, 3);

    DynamicArray<DynamicArray<int>> matrix(2);
    matrix.set(0, row1);

    LinkedList<DynamicArray<int>> list_of_arrays;

    DynamicArray<int> row1(3);
    row1.set(0, 1); row1.set(1, 2); row1.set(2, 3);

    DynamicArray<int> row2(2);
    row2.set(0, 10); row2.set(1, 20);

    list_of_arrays.append(row1);
    list_of_arrays.append(row2);
    // std::cout << "Complete!" << std::endl;
    return 0;
}

