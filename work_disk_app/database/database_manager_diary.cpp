#include "database_manager.h"

bool DatabaseManager::insertDiaryEntry(const DiaryEntry& diary)
{
    const char* sql =
        "INSERT INTO diary_entries "
        "(user_id, title, content, mood, created_at, updated_at) "
        "VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, diary.userId);
    sqlite3_bind_text(stmt, 2, diary.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, diary.content.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, diary.mood.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, diary.createdAt.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, diary.updatedAt.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

std::vector<DiaryEntry> DatabaseManager::getAllDiaryEntries()
{
    std::vector<DiaryEntry> diaries;

    const char* sql =
        "SELECT id, user_id, title, content, mood, created_at, updated_at "
        "FROM diary_entries;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return diaries;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        DiaryEntry diary;

        diary.id = sqlite3_column_int(stmt, 0);
        diary.userId = sqlite3_column_int(stmt, 1);
        diary.title =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        diary.content =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        diary.mood =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        diary.createdAt =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        diary.updatedAt =
            reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

        diaries.push_back(diary);
    }

    sqlite3_finalize(stmt);

    return diaries;
}

bool DatabaseManager::updateDiaryEntry(const DiaryEntry& diary)
{
    const char* sql =
        "UPDATE diary_entries "
        "SET user_id = ?, "
        "title = ?, "
        "content = ?, "
        "mood = ?, "
        "created_at = ?, "
        "updated_at = ? "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, diary.userId);
    sqlite3_bind_text(stmt, 2, diary.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, diary.content.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, diary.mood.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, diary.createdAt.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, diary.updatedAt.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 7, diary.id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

bool DatabaseManager::deleteDiaryEntry(int diaryId)
{
    const char* sql =
        "DELETE FROM diary_entries "
        "WHERE id = ?;";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_int(stmt, 1, diaryId);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}