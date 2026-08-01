#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "../database/database_manager.h"
#include "../database/user_model.h"

#include <vector>


class UserService
{
private:

    DatabaseManager& dbManager;


public:

    UserService(DatabaseManager& db);


    bool createUser(const User& user);

    std::vector<User> getUsers();

    bool updateUser(const User& user);

    bool deleteUser(int userId);

};


#endif