#include "database_manager.h"

bool DatabaseManager::insertSetting(const Setting& setting)
{
    const char* sql =
        "INSERT INTO settings "
        "(setting_key, setting_value) "
        "VALUES (?, ?);";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, setting.key.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, setting.value.c_str(), -1, SQLITE_TRANSIENT);

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

std::vector<Setting> DatabaseManager::getAllSettings()
{
    std::vector<Setting> settings;

    const char* sql =
        "SELECT id, setting_key, setting_value "
        "FROM settings;";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK)
        return settings;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Setting setting;

        setting.id = sqlite3_column_int(stmt, 0);
        setting.key =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        setting.value =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        settings.push_back(setting);
    }

    sqlite3_finalize(stmt);

    return settings;
}

bool DatabaseManager::updateSetting(const Setting& setting)
{
    const char* sql =
        "UPDATE settings "
        "SET setting_key = ?, "
        "setting_value = ? "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, setting.key.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, setting.value.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, setting.id);

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}

bool DatabaseManager::deleteSetting(int settingId)
{
    const char* sql =
        "DELETE FROM settings "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    if (result != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, settingId);

    result = sqlite3_step(stmt);

    sqlite3_finalize(stmt);

    return result == SQLITE_DONE;
}