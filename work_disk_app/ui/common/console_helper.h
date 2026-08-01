#ifndef CONSOLE_HELPER_H
#define CONSOLE_HELPER_H

#include <string>

namespace ui
{

class ConsoleHelper
{
public:
    static void clearScreen();

    static void pauseScreen();

    static void printHeader(const std::string& title);

    static void printSeparator();

    static void printSuccess(const std::string& message);

    static void printError(const std::string& message);

    static int inputInt();

    static std::string inputString();

    static bool confirmAction(const std::string& message);
};

} // namespace ui

#endif // CONSOLE_HELPER_H