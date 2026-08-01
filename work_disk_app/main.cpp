#include "database/database_manager.h"

#include "services/user_service.h"
#include "services/work_entry_service.h"

#include "ui/main_menu.h"

#include <iostream>

int main()
{
    DatabaseManager dbManager;

    if (!dbManager.initializeDatabase())
    {
        std::cout << "Database initialization failed!\n";
        return 1;
    }

    if (!dbManager.createTables())
    {
        std::cout << "Table creation failed!\n";
        return 1;
    }

    UserService userService(dbManager);
    WorkEntryService workEntryService(dbManager);

    ui::MainMenu mainMenu;
    mainMenu.show();

    return 0;
}