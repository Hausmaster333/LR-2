#include "menu.h"
#include "sequence.h"
#include <iostream>
#include <cstdlib>

const int MAX_SEQUENCES = 10;

Sequence<int>* sequences[MAX_SEQUENCES];
int seq_count = 0;

BitSequence* bit_sequences[MAX_SEQUENCES];
int bit_seq_count = 0;

int square(const int& x) {
    return x * x;
}

bool is_positive(const int& x) {
    return x > 0;
}

int sum(const int& a, const int& b) {
    return a + b;
}

void print_sequence(Sequence<int>* seq) {
    std::cout << "[";
    for (int i = 0; i < seq->get_count(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << seq->get(i);
    }
    std::cout << "]" << std::endl;
}

void print_bit_sequence(BitSequence* seq) {
    std::cout << "[";
    for (int i = 0; i < seq->get_count(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << seq->get(i).get();
    }
    std::cout << "]" << std::endl;
}

// === Выбор последовательности по индексу ===

int select_sequence(const char* prompt) {
    if (seq_count == 0) {
        std::cout << "No sequences created" << std::endl;
        return -1;
    }
    std::cout << prompt << std::endl;
    for (int i = 0; i < seq_count; i++) {
        std::cout << i << ": ";
        print_sequence(sequences[i]);
    }
    std::cout << "Index: ";
    int idx;
    std::cin >> idx;
    if (idx < 0 || idx >= seq_count) {
        std::cout << "Invalid index" << std::endl;
        return -1;
    }
    return idx;
}

int select_bit_sequence(const char* prompt) {
    if (bit_seq_count == 0) {
        std::cout << "No BitSequences created" << std::endl;
        return -1;
    }
    std::cout << prompt << std::endl;
    for (int i = 0; i < bit_seq_count; i++) {
        std::cout << i << ": ";
        print_bit_sequence(bit_sequences[i]);
    }
    std::cout << "Index: ";
    int idx;
    std::cin >> idx;
    if (idx < 0 || idx >= bit_seq_count) {
        std::cout << "Invalid index" << std::endl;
        return -1;
    }
    return idx;
}

// === 1. Создание последовательности ===

void menu_create_sequence() {
    std::cout << "\n=== Create Sequence ===" << std::endl;
    std::cout << "1. MutableArraySequence<int>" << std::endl;
    std::cout << "2. MutableListSequence<int>" << std::endl;
    std::cout << "3. ImmutableArraySequence<int>" << std::endl;
    std::cout << "4. ImmutableListSequence<int>" << std::endl;
    std::cout << "5. BitSequence" << std::endl;
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    if (choice == 5) {
        if (bit_seq_count >= MAX_SEQUENCES) {
            std::cout << "Max BitSequences reached" << std::endl;
            return;
        }
        std::cout << "Enter number of bits: ";
        int n;
        std::cin >> n;
        BitSequence* bs = new BitSequence(new MutableArraySequence<Bit>());
        for (int i = 0; i < n; i++) {
            std::cout << "Bit " << i << " (0/1): ";
            int val;
            std::cin >> val;
            bs->append(Bit(val));
        }
        bit_sequences[bit_seq_count++] = bs;
        std::cout << "BitSequence created (bit index: " << bit_seq_count - 1 << ")" << std::endl;
        return;
    }

    if (seq_count >= MAX_SEQUENCES) {
        std::cout << "Max sequences reached" << std::endl;
        return;
    }

    std::cout << "Enter number of elements: ";
    int n;
    std::cin >> n;

    Sequence<int>* seq = nullptr;
    switch (choice) {
        case 1: seq = new MutableArraySequence<int>(); break;
        case 2: seq = new MutableListSequence<int>(); break;
        case 3: seq = new ImmutableArraySequence<int>(); break;
        case 4: seq = new ImmutableListSequence<int>(); break;
        default:
            std::cout << "Invalid choice" << std::endl;
            return;
    }

    for (int i = 0; i < n; i++) {
        std::cout << "Element " << i << ": ";
        int val;
        std::cin >> val;
        Sequence<int>* result = seq->append(val);
        if (result != seq) { // Immutable — заменяем указатель
            delete seq;
            seq = result;
        }
    }

    sequences[seq_count++] = seq;
    std::cout << "Sequence created (index: " << seq_count - 1 << ")" << std::endl;
}

// === 2. Добавление элемента ===

void menu_add_element() {
    int idx = select_sequence("Select sequence:");
    if (idx == -1) return;

    std::cout << "Enter element: ";
    int val;
    std::cin >> val;

    Sequence<int>* result = sequences[idx]->append(val);
    if (result != sequences[idx]) { // Immutable
        delete sequences[idx];
        sequences[idx] = result;
    }
    std::cout << "Element added" << std::endl;
}

// === 3. Печать последовательности ===

void menu_print_sequence() {
    if (seq_count == 0 && bit_seq_count == 0) {
        std::cout << "No sequences created" << std::endl;
        return;
    }
    std::cout << "\n--- Sequence<int> ---" << std::endl;
    for (int i = 0; i < seq_count; i++) {
        std::cout << "[" << i << "]: ";
        print_sequence(sequences[i]);
    }
    std::cout << "\n--- BitSequence ---" << std::endl;
    for (int i = 0; i < bit_seq_count; i++) {
        std::cout << "[" << i << "]: ";
        print_bit_sequence(bit_sequences[i]);
    }
}

// === 4. Получение элемента ===

void menu_get_element() {
    int idx = select_sequence("Select sequence:");
    if (idx == -1) return;

    std::cout << "Enter element index: ";
    int pos;
    std::cin >> pos;

    try {
        std::cout << "Element: " << sequences[idx]->get(pos) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// === 5. Получение подпоследовательности ===

void menu_get_subsequence() {
    int idx = select_sequence("Select sequence:");
    if (idx == -1) return;

    std::cout << "Start index: ";
    int start;
    std::cin >> start;
    std::cout << "End index: ";
    int end;
    std::cin >> end;

    try {
        Sequence<int>* sub = sequences[idx]->get_sub_sequence(start, end);
        std::cout << "Subsequence: ";
        print_sequence(sub);

        if (seq_count < MAX_SEQUENCES) {
            sequences[seq_count++] = sub;
            std::cout << "Saved as index " << seq_count - 1 << std::endl;
        } else {
            delete sub;
            std::cout << "No space to save, result deleted" << std::endl;
        }
    } catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// === 6. Конкатенация ===

void menu_concat_sequences() {
    int idx1 = select_sequence("Select first sequence:");
    if (idx1 == -1) return;
    int idx2 = select_sequence("Select second sequence:");
    if (idx2 == -1) return;

    Sequence<int>* result = sequences[idx1]->concat(sequences[idx2]);
    std::cout << "Result: ";
    print_sequence(result);

    if (seq_count < MAX_SEQUENCES) {
        sequences[seq_count++] = result;
        std::cout << "Saved as index " << seq_count - 1 << std::endl;
    } else {
        delete result;
        std::cout << "No space to save, result deleted" << std::endl;
    }
}

// === 7. Map (square) ===

void menu_map() {
    int idx = select_sequence("Select sequence:");
    if (idx == -1) return;

    Sequence<int>* result = sequences[idx]->map(square);
    std::cout << "Result map(square): ";
    print_sequence(result);

    if (result != sequences[idx] && seq_count < MAX_SEQUENCES) {
        sequences[seq_count++] = result;
        std::cout << "Saved as index " << seq_count - 1 << std::endl;
    } else if (result == sequences[idx]) {
        std::cout << "Sequence modified in place" << std::endl;
    } else {
        delete result;
        std::cout << "No space to save, result deleted" << std::endl;
    }
}

// === 8. Where (positive) ===

void menu_where() {
    int idx = select_sequence("Select sequence:");
    if (idx == -1) return;

    Sequence<int>* result = sequences[idx]->where(is_positive);
    std::cout << "Result where(positive): ";
    print_sequence(result);

    if (result != sequences[idx] && seq_count < MAX_SEQUENCES) {
        sequences[seq_count++] = result;
        std::cout << "Saved as index " << seq_count - 1 << std::endl;
    } else if (result == sequences[idx]) {
        std::cout << "Sequence modified in place" << std::endl;
    } else {
        delete result;
        std::cout << "No space to save, result deleted" << std::endl;
    }
}

// === 9. Reduce (sum) ===

void menu_reduce() {
    int idx = select_sequence("Select sequence:");
    if (idx == -1) return;

    if (sequences[idx]->get_count() == 0) {
        std::cout << "Sequence is empty" << std::endl;
        return;
    }

    int result = sequences[idx]->reduce(sum, 0);
    std::cout << "Result reduce(sum): " << result << std::endl;
}

// === 10. BitSequence операции ===

void menu_bit_operations() {
    std::cout << "\n=== BitSequence Operations ===" << std::endl;
    std::cout << "1. AND" << std::endl;
    std::cout << "2. OR" << std::endl;
    std::cout << "3. XOR" << std::endl;
    std::cout << "4. NOT" << std::endl;
    std::cout << "Choice: ";

    int choice;
    std::cin >> choice;

    if (choice == 4) {
        int idx = select_bit_sequence("Select BitSequence:");
        if (idx == -1) return;

        BitSequence* result = bit_sequences[idx]->bit_not();
        std::cout << "Result NOT: ";
        print_bit_sequence(result);

        if (bit_seq_count < MAX_SEQUENCES) {
            bit_sequences[bit_seq_count++] = result;
            std::cout << "Saved as bit index " << bit_seq_count - 1 << std::endl;
        } else {
            delete result;
            std::cout << "No space to save, result deleted" << std::endl;
        }
        return;
    }

    int idx1 = select_bit_sequence("Select first BitSequence:");
    if (idx1 == -1) return;
    int idx2 = select_bit_sequence("Select second BitSequence:");
    if (idx2 == -1) return;

    BitSequence* result = nullptr;
    switch (choice) {
        case 1: result = bit_sequences[idx1]->bit_and(*bit_sequences[idx2]); break;
        case 2: result = bit_sequences[idx1]->bit_or(*bit_sequences[idx2]); break;
        case 3: result = bit_sequences[idx1]->bit_xor(*bit_sequences[idx2]); break;
        default:
            std::cout << "Invalid choice" << std::endl;
            return;
    }

    std::cout << "Result: ";
    print_bit_sequence(result);

    if (bit_seq_count < MAX_SEQUENCES) {
        bit_sequences[bit_seq_count++] = result;
        std::cout << "Saved as bit index " << bit_seq_count - 1 << std::endl;
    } else {
        delete result;
        std::cout << "No space to save, result deleted" << std::endl;
    }
}

// === 11. Запуск тестов ===

void menu_run_tests() {
    std::cout << "\nRunning tests..." << std::endl;
    int ret = system("make tests && ./tests");
    if (ret != 0) {
        std::cout << "Error running tests" << std::endl;
    }
}

// === Главное меню ===

void run_menu() {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n==== Main Menu ====" << std::endl;
        std::cout << "1. Create sequence" << std::endl;
        std::cout << "2. Add element" << std::endl;
        std::cout << "3. Print sequence" << std::endl;
        std::cout << "4. Get element" << std::endl;
        std::cout << "5. Get subsequence" << std::endl;
        std::cout << "6. Concat sequences" << std::endl;
        std::cout << "7. Map (square)" << std::endl;
        std::cout << "8. Where (positive)" << std::endl;
        std::cout << "9. Reduce (sum)" << std::endl;
        std::cout << "10. BitSequence operations" << std::endl;
        std::cout << "11. Run tests" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: menu_create_sequence(); break;
            case 2: menu_add_element(); break;
            case 3: menu_print_sequence(); break;
            case 4: menu_get_element(); break;
            case 5: menu_get_subsequence(); break;
            case 6: menu_concat_sequences(); break;
            case 7: menu_map(); break;
            case 8: menu_where(); break;
            case 9: menu_reduce(); break;
            case 10: menu_bit_operations(); break;
            case 11: menu_run_tests(); break;
            case 0: std::cout << "Exit" << std::endl; break;
            default: std::cout << "Invalid choice" << std::endl; break;
        }
    }

    // Очистка памяти
    for (int i = 0; i < seq_count; i++) {
        delete sequences[i];
    }
    for (int i = 0; i < bit_seq_count; i++) {
        delete bit_sequences[i];
    }
}
