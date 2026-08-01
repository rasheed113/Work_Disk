#include "dashboard.h"

#include "../common/console_helper.h"

#include <iostream>

namespace ui
{

void Dashboard::show()
{
    ConsoleHelper::clearScreen();

    displayHeader();

    displaySummary();

    ConsoleHelper::pauseScreen();
}

void Dashboard::displayHeader()
{
    ConsoleHelper::printHeader("Dashboard");
}

void Dashboard::displaySummary()
{
    std::cout << "ERGS Dynamics\n";
    std::cout << "Work_Disk Dashboard\n";
}

} // namespace ui
