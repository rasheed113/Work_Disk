#include "database_manager.h"

bool DatabaseManager::insertDevice(const Device& device)
{
    const char* sql =
        "INSERT INTO devices "
        "(user_id, device_name, device_id, platform, created_at) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, device.userId);
    sqlite3_bind_text(stmt, 2, device.deviceName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, device.deviceId.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, device.platform.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, device.createdAt.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

std::vector<Device> DatabaseManager::getAllDevices()
{
    std::vector<Device> devices;

    const char* sql =
        "SELECT id, user_id, device_name, device_id, platform, created_at "
        "FROM devices;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return devices;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        Device device;

        device.id = sqlite3_column_int(stmt, 0);
        device.userId = sqlite3_column_int(stmt, 1);
        device.deviceName =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        device.deviceId =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        device.platform =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        device.createdAt =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        devices.push_back(device);
    }

    sqlite3_finalize(stmt);

    return devices;
}

bool DatabaseManager::updateDevice(const Device& device)
{
    const char* sql =
        "UPDATE devices "
        "SET user_id = ?, "
        "device_name = ?, "
        "device_id = ?, "
        "platform = ?, "
        "created_at = ? "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, device.userId);
    sqlite3_bind_text(stmt, 2, device.deviceName.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, device.deviceId.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, device.platform.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, device.createdAt.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, device.id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

bool DatabaseManager::deleteDevice(int deviceId)
{
    const char* sql =
        "DELETE FROM devices "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, deviceId);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}