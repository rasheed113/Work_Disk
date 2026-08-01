#include "work_entry_service.h"

WorkEntryService::WorkEntryService(DatabaseManager& db)
    : dbManager(db)
{
}

bool WorkEntryService::createWorkEntry(const WorkEntry& entry)
{
    return dbManager.insertWorkEntry(entry);
}

std::vector<WorkEntry> WorkEntryService::getWorkEntries()
{
    return dbManager.getAllWorkEntries();
}

bool WorkEntryService::updateWorkEntry(const WorkEntry& entry)
{
    return dbManager.updateWorkEntry(entry);
}

bool WorkEntryService::deleteWorkEntry(int entryId)
{
    return dbManager.deleteWorkEntry(entryId);
}