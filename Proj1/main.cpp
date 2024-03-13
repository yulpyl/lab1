#include "Functions.h"
#include <iostream>
#include <vector>
#include <chrono>

void interactiveMode() {
    int choice;
    std::cout << "\n--- Interactive Mode ---\n";

    do {
        std::cout << "\nOptions:\n"
            << "1. Add Message\n"
            << "2. Search Messages\n"
            << "3. Modify Message\n"
            << "4. Delete Message\n"
            << "5. Display All Messages\n"
            << "0. Exit Interactive Mode\n"
            << "Enter your choice: ";
        std::cin >> choice;

        // Очищення буфера вводу для уникнення проблем зі вводом
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            addMessage();
            break;
        case 2:
            searchMessages();
            break;
        case 3:
            modifyMessage();
            break;
        case 4:
            deleteMessage();
            break;
        case 5:
            displayAllMessages();
            break;
        case 0:
            std::cout << "Exiting Interactive Mode...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);
}

void demoMode() {
    std::cout << "Demo Mode Activated\n";
    // Автоматичне додавання демо-повідомлень
    MessageLog demoMsg1 = { 1, "Demo message 1", std::time(nullptr), DEBUG, 10, 0.5 };
    MessageLog demoMsg2 = { 2, "Demo message 2", std::time(nullptr), INFO, 20, 0.4 };
    messages.push_back(demoMsg1);
    messages.push_back(demoMsg2);
    // Автоматичний пошук і відображення демо-повідомлень
    displayAllMessages();
}

void benchmarkMode() {
    std::cout << "Benchmark Mode Activated\n";
    auto start = std::chrono::high_resolution_clock::now();
    // Ваш код для виконання бенчмарк-тестів
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Benchmark completed in " << diff.count() << " seconds\n";
}

int main() {
    int mode;
    do {
        std::cout << "\nMain Menu:\n"
            << "1. Enter Interactive Mode\n"
            << "2. Demo Mode\n"
            << "3. Benchmark Mode\n"
            << "0. Exit Program\n"
            << "Enter your choice: ";
        std::cin >> mode;

        // Очищення буфера вводу для уникнення проблем зі вводом
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (mode) {
        case 1:
            interactiveMode();
            break;
        case 2:
            demoMode();
            break;
        case 3:
            benchmarkMode();
            break;
        case 0:
            std::cout << "Exiting Program...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (mode != 0);

    return 0;
}
