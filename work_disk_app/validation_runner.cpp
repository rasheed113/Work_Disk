
#include <iostream>
#include <vector>
#include <ctime>

#include "database/database_manager.h"
#include "database/user_model.h"
#include "database/work_entry_model.h"

#include "services/user_service.h"
#include "services/work_entry_service.h"


int main()
{
    DatabaseManager dbManager;


    if (!dbManager.initializeDatabase())
    {
        std::cout << "Database initialization failed!" << std::endl;
        return 1;
    }


    if (!dbManager.createTables())
    {
        std::cout << "Table creation failed!" << std::endl;
        return 1;
    }


    UserService userService(dbManager);
    WorkEntryService workEntryService(dbManager);



    std::cout << "\n===== USER CREATE TEST =====\n";


    User user;

    user.fullName = "Day14 Test User";

    user.email =
        "day14_test_" + std::to_string(std::time(nullptr))
        + "@example.com";

    user.phone = "03000000000";
    user.passwordHash = "test_hash";


    if (userService.createUser(user))
    {
        std::cout << "User created successfully!" << std::endl;
    }
    else
    {
        std::cout << "User creation failed!" << std::endl;
    }



    // Get created user ID

    std::vector<User> users = userService.getUsers();


    int testUserId = -1;


    for (const User& u : users)
    {
        if (u.email == user.email)
        {
            testUserId = u.id;
            break;
        }
    }



    if (testUserId == -1)
    {
        std::cout << "Test user ID not found!" << std::endl;
        return 1;
    }


    std::cout
        << "Created User ID: "
        << testUserId
        << std::endl;



    std::cout << "\n===== USER UPDATE TEST =====\n";


    User updatedUser;

    updatedUser.id = testUserId;
    updatedUser.fullName = "Day14 Updated User";
    updatedUser.email = user.email;
    updatedUser.phone = "03111111111";
    updatedUser.passwordHash = "updated_hash";


    if (userService.updateUser(updatedUser))
    {
        std::cout << "User updated successfully!" << std::endl;
    }
    else
    {
        std::cout << "User update failed!" << std::endl;
    }



    std::cout << "\n===== WORK ENTRY TEST =====\n";


    WorkEntry entry;


    entry.userId = testUserId;
    entry.date = "2026-07-26";
    entry.itemName = "Shirt";
    entry.quantity = 100;
    entry.rate = 5.0;
    entry.amount = 500.0;
    entry.notes = "Day14 Validation Entry";


    if (workEntryService.createWorkEntry(entry))
    {
        std::cout << "WorkEntry inserted successfully!"
                  << std::endl;
    }
    else
    {
        std::cout << "WorkEntry insertion failed!"
                  << std::endl;
    }



    std::cout << "\n===== USER DELETE TEST =====\n";


    if (userService.deleteUser(testUserId))
    {
        std::cout << "User deleted successfully!"
                  << std::endl;
    }
    else
    {
        std::cout << "User delete failed!"
                  << std::endl;
    }



    std::cout << "\n===== FINAL USERS =====\n";


    std::vector<User> finalUsers =
        userService.getUsers();


    for (const User& u : finalUsers)
    {
        std::cout
            << "ID: "
            << u.id
            << " | Name: "
            << u.fullName
            << " | Email: "
            << u.email
            << std::endl;
    }



    std::cout << "\n===== DAY 14 VALIDATION COMPLETE =====\n";


    return 0;
}
