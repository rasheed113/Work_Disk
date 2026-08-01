#include "main_menu.h"

#include "common/console_helper.h"
#include "dashboard/dashboard.h"

#include <iostream>

namespace ui
{

void MainMenu::show()
{
    int choice = -1;

    while (choice != 0)
    {
        ConsoleHelper::clearScreen();

        displayMenu();

        std::cout << "\nEnter your choice: ";
        choice = ConsoleHelper::inputInt();

        handleChoice(choice);
    }
}

void MainMenu::displayMenu()
{
    ConsoleHelper::printHeader("ERGS Dynamics - Work_Disk");

    std::cout << "1. Dashboard\n";

    std::cout << "0. Exit\n";
}

void MainMenu::handleChoice(int choice)
{
    switch (choice)
    {
        case 1:
{
    Dashboard dashboard;
    dashboard.show();
    break;
}

        case 2:
            std::cout << "User module coming soon.\n";
            break;

        case 3:
            std::cout << "Work Entry module coming soon.\n";
            break;

        case 4:
            std::cout << "Finance module coming soon.\n";
            break;

        case 5:
            std::cout << "Diary module coming soon.\n";
            break;

        case 6:
            std::cout << "Settings module coming soon.\n";
            break;

        case 0:
            std::cout << "Exiting Work_Disk...\n";
            break;

        default:
            ConsoleHelper::printError("Invalid choice.");
            break;
    }
}

} // namespace ui