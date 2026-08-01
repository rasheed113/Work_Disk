#ifndef DIARY_SERVICE_H
#define DIARY_SERVICE_H

#include "../database/database_manager.h"
#include "../database/diary_model.h"

#include <vector>

class DiaryService
{
private:
    DatabaseManager& dbManager;

public:
    DiaryService(DatabaseManager& db);

    bool createDiaryEntry(const DiaryEntry& diary);

    std::vector<DiaryEntry> getDiaryEntries();

    bool updateDiaryEntry(const DiaryEntry& diary);

    bool deleteDiaryEntry(int diaryId);
};

#endif