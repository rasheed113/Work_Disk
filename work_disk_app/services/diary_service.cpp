#include "diary_service.h"

DiaryService::DiaryService(DatabaseManager& db)
    : dbManager(db)
{
}

bool DiaryService::createDiaryEntry(const DiaryEntry& diary)
{
    return dbManager.insertDiaryEntry(diary);
}

std::vector<DiaryEntry> DiaryService::getDiaryEntries()
{
    return dbManager.getAllDiaryEntries();
}

bool DiaryService::updateDiaryEntry(const DiaryEntry& diary)
{
    return dbManager.updateDiaryEntry(diary);
}

bool DiaryService::deleteDiaryEntry(int diaryId)
{
    return dbManager.deleteDiaryEntry(diaryId);
}