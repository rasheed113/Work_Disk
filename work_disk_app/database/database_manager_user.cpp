#include "database_manager.h"

bool DatabaseManager::insertUser(const User& user)
{
    const char* sql =
        "INSERT INTO users "
        "(full_name, email, phone, password_hash) "
        "VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &stmt,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_text(
        stmt,
        1,
        user.fullName.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        2,
        user.email.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        3,
        user.phone.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        4,
        user.passwordHash.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

std::vector<User> DatabaseManager::getAllUsers()
{
    std::vector<User> users;

    const char* sql =
        "SELECT id, full_name, email, phone, password_hash "
        "FROM users;";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &stmt,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        return users;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        User user;

        user.id = sqlite3_column_int(stmt, 0);

        user.fullName =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 1));

        user.email =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 2));

        user.phone =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 3));

        user.passwordHash =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 4));

        users.push_back(user);
    }

    sqlite3_finalize(stmt);

    return users;
}

bool DatabaseManager::updateUser(const User& user)
{
    const char* sql =
        "UPDATE users "
        "SET full_name = ?, "
        "email = ?, "
        "phone = ?, "
        "password_hash = ? "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &stmt,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_text(
        stmt,
        1,
        user.fullName.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        2,
        user.email.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        3,
        user.phone.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        4,
        user.passwordHash.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_int(
        stmt,
        5,
        user.id
    );

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

bool DatabaseManager::deleteUser(int userId)
{
    const char* sql =
        "DELETE FROM users "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(
        db,
        sql,
        -1,
        &stmt,
        nullptr
    );

    if (result != SQLITE_OK)
    {
        return false;
    }


    sqlite3_bind_int(
        stmt,
        1,
        userId
    );


    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);


    return result == SQLITE_DONE;
}