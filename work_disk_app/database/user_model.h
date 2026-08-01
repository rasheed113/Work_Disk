#ifndef USER_MODEL_H
#define USER_MODEL_H

#include <string>

class User
{
public:
    int id;
    std::string fullName;
    std::string email;
    std::string phone;
    std::string passwordHash;

    User();
};

#endif