#include "console_helper.h"

#include <iostream>
#include <limits>

namespace ui
{

void ConsoleHelper::clearScreen()
{
    std::cout << "\033[2J\033[H";
}

void ConsoleHelper::pauseScreen()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void ConsoleHelper::printHeader(const std::string& title)
{
    std::cout << "\n========================================\n";
    std::cout << " " << title << '\n';
    std::cout << "========================================\n";
}

void ConsoleHelper::printSeparator()
{
    std::cout << "----------------------------------------\n";
}

void ConsoleHelper::printSuccess(const std::string& message)
{
    std::cout << "[SUCCESS] " << message << '\n';
}

void ConsoleHelper::printError(const std::string& message)
{
    std::cout << "[ERROR] " << message << '\n';
}

int ConsoleHelper::inputInt()
{
    int value;
    std::cin >> value;
    return value;
}

std::string ConsoleHelper::inputString()
{
    std::string value;
    std::getline(std::cin >> std::ws, value);
    return value;
}

bool ConsoleHelper::confirmAction(const std::string& message)
{
    char choice;

    std::cout << message << " (y/n): ";
    std::cin >> choice;

    return (choice == 'y' || choice == 'Y');
}

} // namespace ui