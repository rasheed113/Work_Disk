#include "database_manager.h"

#include <iostream>

DatabaseManager::DatabaseManager()
{
    db = nullptr;
}

DatabaseManager::~DatabaseManager()
{
    if (db != nullptr)
    {
        sqlite3_close(db);
    }
}

bool DatabaseManager::initializeDatabase()
{
    int result = sqlite3_open("work_disk.db", &db);

    if (result != SQLITE_OK)
    {
        return false;
    }

    return true;
}

sqlite3* DatabaseManager::getDatabase()
{
    return db;
}

bool DatabaseManager::createTables()
{
    const char* sql = R"(

        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            full_name TEXT NOT NULL,
            email TEXT UNIQUE,
            phone TEXT,
            password_hash TEXT,
            created_at TEXT,
            updated_at TEXT
        );

        CREATE TABLE IF NOT EXISTS settings (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            setting_key TEXT,
            setting_value TEXT,
            updated_at TEXT
        );

        CREATE TABLE IF NOT EXISTS work_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            date TEXT,
            item_name TEXT,
            quantity INTEGER,
            rate REAL,
            amount REAL,
            notes TEXT,
            created_at TEXT,
            updated_at TEXT
        );

        CREATE TABLE IF NOT EXISTS finance_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            type TEXT,
            amount REAL,
            note TEXT,
            entry_date TEXT,
            created_at TEXT
        );

        CREATE TABLE IF NOT EXISTS diary_entries (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            title TEXT,
            content TEXT,
            mood TEXT,
            created_at TEXT,
            updated_at TEXT
        );

        CREATE TABLE IF NOT EXISTS devices (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            user_id INTEGER,
            device_name TEXT,
            device_id TEXT,
            platform TEXT,
            created_at TEXT
        );

    )";

    char* errorMessage = nullptr;

    int result = sqlite3_exec(
        db,
        sql,
        nullptr,
        nullptr,
        &errorMessage
    );

    if (result != SQLITE_OK)
    {
        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

// Connection Status

bool DatabaseManager::isConnected() const
{
    return db != nullptr;
}

// SQL Utilities

bool DatabaseManager::executeSQL(const std::string& sql)
{
    char* errMsg = nullptr;

    int rc = sqlite3_exec(
        db,
        sql.c_str(),
        nullptr,
        nullptr,
        &errMsg
    );

    if (rc != SQLITE_OK)
    {
        if (errMsg)
        {
            std::cerr << "SQL Error: "
                      << errMsg
                      << std::endl;

            sqlite3_free(errMsg);
        }

        return false;
    }

    return true;
}

// Transaction Control

bool DatabaseManager::beginTransaction()
{
    return executeSQL("BEGIN TRANSACTION;");
}

bool DatabaseManager::commitTransaction()
{
    return executeSQL("COMMIT;");
}

bool DatabaseManager::rollbackTransaction()
{
    return executeSQL("ROLLBACK;");
}

// Error Handling

std::string DatabaseManager::getLastError() const
{
    if (!db)
    {
        return "Database not connected.";
    }

    return sqlite3_errmsg(db);
}