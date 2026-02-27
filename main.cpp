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
    // std::cout << "Complete!" << std::endl;
    return 0;
}