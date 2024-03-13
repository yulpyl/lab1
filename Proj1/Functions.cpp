#include "Functions.h"
#include <iostream>
#include <vector>
#include <chrono>

std::vector<MessageLog> messages;

void addMessage() {
    MessageLog msg;
    msg.id = static_cast<int>(messages.size()) + 1;

    std::cout << "Enter message text: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, msg.messageText);

    int type;
    std::cout << "Enter message type (0 - DEBUG, 1 - INFO, 2 - WARNING, 3 - ERROR, 4 - FATAL): ";
    std::cin >> type;
    if (std::cin.fail() || type < 0 || type > 4) {
        std::cin.clear(); // очистити прапори помилок
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ігнорувати неправильний ввід
        std::cout << "Invalid message type. Please enter a number between 0 and 4.\n";
        return;
    }
    msg.messageType = static_cast<MessageType>(type);

    int priority;
    std::cout << "Enter message priority (0-100): ";
    std::cin >> priority;
    if (std::cin.fail() || priority < 0 || priority > 100) {
        std::cin.clear(); // очистити прапори помилок
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ігнорувати неправильний ввід
        std::cout << "Invalid priority. Please enter a number between 0 and 100.\n";
        return;
    }
    msg.priority = priority;

    double loadLevel;
    std::cout << "Enter system load level (0.0-1.0): ";
    std::cin >> loadLevel;
    if (std::cin.fail() || loadLevel < 0.0 || loadLevel > 1.0) {
        std::cin.clear(); // очистити прапори помилок
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ігнорувати неправильний ввід
        std::cout << "Invalid load level. Please enter a number between 0.0 and 1.0.\n";
        return;
    }
    msg.loadLevel = loadLevel;

    msg.timestamp = std::time(nullptr);

    messages.push_back(msg);
    std::cout << "Message added successfully.\n";
}

void searchMessages() {
    int searchOption;
    std::cout << "Select search criteria:\n";
    std::cout << "1. Message Type\n";
    std::cout << "2. Load Level\n";
    std::cout << "3. Text Fragment\n";
    std::cout << "4. Date Range\n";
    std::cout << "Enter your choice: ";
    std::cin >> searchOption;

    if (std::cin.fail() || searchOption < 1 || searchOption > 4) {
        std::cin.clear(); // очистити прапори помилок
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ігнорувати неправильний ввід
        std::cout << "Invalid option. Please try again.\n";
        return;
    }


    switch (searchOption) {
    case 1: {
        int type;
        std::cout << "Enter message type (0 - DEBUG, 1 - INFO, 2 - WARNING, 3 - ERROR, 4 - FATAL): ";
        std::cin >> type;
        MessageType searchType = static_cast<MessageType>(type);
        for (const auto& msg : messages) {
            if (msg.messageType == searchType) {
                std::cout << "Found Message - ID: " << msg.id << ", Text: " << msg.messageText << std::endl;
            }
        }
        break;
    }
    case 2: {
        double minLoadLevel;
        std::cout << "Enter minimum load level (0.0-1.0): ";
        std::cin >> minLoadLevel;
        for (const auto& msg : messages) {
            if (msg.loadLevel >= minLoadLevel) {
                std::cout << "Found Message - ID: " << msg.id << ", Load Level: " << msg.loadLevel << std::endl;
            }
        }
        break;
    }
    case 3: {
        std::string textFragment;
        std::cout << "Enter text fragment: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистити буфер вводу
        std::getline(std::cin, textFragment);
        for (const auto& msg : messages) {
            if (msg.messageText.find(textFragment) != std::string::npos) {
                std::cout << "Found Message - ID: " << msg.id << ", Text: " << msg.messageText << std::endl;
            }
        }
        break;
    }
    case 4: {
        std::string startDateStr, endDateStr;
        std::cout << "Enter start date [day month year]: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, startDateStr);

        std::cout << "Enter end date [day month year]: ";
        std::getline(std::cin, endDateStr);

        std::tm startDate = {}, endDate = {};
        std::istringstream startIss(startDateStr), endIss(endDateStr);
        if (!(startIss >> std::get_time(&startDate, "%d %m %Y")) || !(endIss >> std::get_time(&endDate, "%d %m %Y"))) {
            std::cout << "Invalid date format. Please try again using [day month year].\n";
            return;
        }

        std::time_t startTime = std::mktime(&startDate), endTime = std::mktime(&endDate);
        if (startTime == -1 || endTime == -1 || startTime > endTime) {
            std::cout << "Invalid date range. Start date must be earlier than end date.\n";
            return;
        }

        for (const auto& msg : messages) {
            if (msg.timestamp >= startTime && msg.timestamp <= endTime) {
                std::tm tm;
                // Замінюємо нижченаведений рядок коду на використання localtime_s
                localtime_s(&tm, &msg.timestamp);
                char buffer[80];
                // Використовуємо strftime, оскільки localtime_s не працює з std::put_time
                strftime(buffer, sizeof(buffer), "%d %m %Y", &tm);
                std::cout << "Found Message - ID: " << msg.id << ", Date: " << buffer << std::endl;
            }
        }
        break;
    }
    default:
        std::cout << "Invalid option. Please try again.\n";
        break;
    }
}

void modifyMessage() {
    int id;
    std::cout << "Enter ID of message to modify: ";
    std::cin >> id;

    for (auto& msg : messages) {
        if (msg.id == id) {
            std::cout << "Enter new message text: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::getline(std::cin, msg.messageText);
            std::cout << "Message modified successfully.\n";
            return;
        }
    }
    std::cout << "Message with ID " << id << " not found.\n";
}

void deleteMessage() {
    int id;
    std::cout << "Enter ID of message to delete: ";
    std::cin >> id;

    auto it = std::remove_if(messages.begin(), messages.end(), [id](const MessageLog& msg) { return msg.id == id; });
    if (it != messages.end()) {
        messages.erase(it, messages.end());
        std::cout << "Message deleted successfully.\n";
    }
    else {
        std::cout << "Message with ID " << id << " not found.\n";
    }
}

void displayAllMessages() {
    for (const auto& msg : messages) {
        std::cout << "ID: " << msg.id << ", Text: " << msg.messageText << ", Type: " << msg.messageType
            << ", Priority: " << msg.priority << ", Load Level: " << msg.loadLevel << std::endl;
    }
}


