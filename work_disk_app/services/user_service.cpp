#include "user_service.h"


UserService::UserService(DatabaseManager& db)
    : dbManager(db)
{

}

bool UserService::createUser(const User& user)
{
    return dbManager.insertUser(user);
}

std::vector<User> UserService::getUsers()
{
    return dbManager.getAllUsers();
}

bool UserService::updateUser(const User& user)
{
    return dbManager.updateUser(user);
}

bool UserService::deleteUser(int userId)
{
    return dbManager.deleteUser(userId);
}