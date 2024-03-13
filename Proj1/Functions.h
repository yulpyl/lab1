#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <limits>
#include <iomanip>
#include <sstream>

enum MessageType { DEBUG, INFO, WARNING, ERROR, FATAL };

struct MessageLog {
    int id;
    std::string messageText;
    std::time_t timestamp;
    MessageType messageType;
    int priority;
    double loadLevel;
};

extern std::vector<MessageLog> messages;

void addMessage();
void searchMessages();
void modifyMessage();
void deleteMessage();
void displayAllMessages();
