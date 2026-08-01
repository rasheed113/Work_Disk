#include "database_manager.h"

bool DatabaseManager::insertFinance(const FinanceEntry& finance)
{
    const char* sql =
        "INSERT INTO finance_entries "
        "(user_id, type, amount, note, entry_date) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, finance.userId);
    sqlite3_bind_text(stmt, 2, finance.type.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, finance.amount);
    sqlite3_bind_text(stmt, 4, finance.note.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, finance.entryDate.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

std::vector<FinanceEntry> DatabaseManager::getAllFinance()
{
    std::vector<FinanceEntry> finances;

    const char* sql =
        "SELECT id, user_id, type, amount, note, entry_date "
        "FROM finance_entries;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return finances;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        FinanceEntry finance;

        finance.id = sqlite3_column_int(stmt, 0);
        finance.userId = sqlite3_column_int(stmt, 1);
        finance.type =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        finance.amount = sqlite3_column_double(stmt, 3);
        finance.note =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        finance.entryDate =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        finances.push_back(finance);
    }

    sqlite3_finalize(stmt);

    return finances;
}

bool DatabaseManager::updateFinance(const FinanceEntry& finance)
{
    const char* sql =
        "UPDATE finance_entries "
        "SET user_id = ?, "
        "type = ?, "
        "amount = ?, "
        "note = ?, "
        "entry_date = ? "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, finance.userId);
    sqlite3_bind_text(stmt, 2, finance.type.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, finance.amount);
    sqlite3_bind_text(stmt, 4, finance.note.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, finance.entryDate.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, finance.id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

bool DatabaseManager::deleteFinance(int financeId)
{
    const char* sql =
        "DELETE FROM finance_entries "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, financeId);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}