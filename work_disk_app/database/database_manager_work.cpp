#include "database_manager.h"

std::vector<WorkEntry> DatabaseManager::getAllWorkEntries()
{
    std::vector<WorkEntry> entries;

    const char* sql =
        "SELECT id, user_id, date, item_name, quantity, "
        "rate, amount, notes "
        "FROM work_entries;";

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
        return entries;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        WorkEntry entry;

        entry.id = sqlite3_column_int(stmt, 0);
        entry.userId = sqlite3_column_int(stmt, 1);

        entry.date =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 2));

        entry.itemName =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 3));

        entry.quantity =
            sqlite3_column_int(stmt, 4);

        entry.rate =
            sqlite3_column_double(stmt, 5);

        entry.amount =
            sqlite3_column_double(stmt, 6);

        entry.notes =
            reinterpret_cast<const char*>(
                sqlite3_column_text(stmt, 7));

        entries.push_back(entry);
    }

    sqlite3_finalize(stmt);

    return entries;
}

bool DatabaseManager::insertWorkEntry(const WorkEntry& entry)
{
    const char* sql =
        "INSERT INTO work_entries "
        "(user_id, date, item_name, quantity, rate, amount, notes) "
        "VALUES (?, ?, ?, ?, ?, ?, ?);";

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

    sqlite3_bind_int(stmt, 1, entry.userId);

    sqlite3_bind_text(
        stmt,
        2,
        entry.date.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        3,
        entry.itemName.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_int(stmt, 4, entry.quantity);

    sqlite3_bind_double(stmt, 5, entry.rate);

    sqlite3_bind_double(stmt, 6, entry.amount);

    sqlite3_bind_text(
        stmt,
        7,
        entry.notes.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

bool DatabaseManager::updateWorkEntry(const WorkEntry& entry)
{
    const char* sql =
        "UPDATE work_entries "
        "SET date = ?, "
        "item_name = ?, "
        "quantity = ?, "
        "rate = ?, "
        "amount = ?, "
        "notes = ? "
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

    sqlite3_bind_text(stmt, 1, entry.date.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, entry.itemName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, entry.quantity);
    sqlite3_bind_double(stmt, 4, entry.rate);
    sqlite3_bind_double(stmt, 5, entry.amount);
    sqlite3_bind_text(stmt, 6, entry.notes.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 7, entry.id);

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

bool DatabaseManager::deleteWorkEntry(int entryId)
{
    const char* sql =
        "DELETE FROM work_entries "
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

    sqlite3_bind_int(stmt, 1, entryId);

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}