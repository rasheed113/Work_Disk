#ifndef WORK_ENTRY_SERVICE_H
#define WORK_ENTRY_SERVICE_H

#include "../database/database_manager.h"
#include "../database/work_entry_model.h"

#include <vector>

class WorkEntryService
{
private:
    DatabaseManager& dbManager;

public:
    WorkEntryService(DatabaseManager& db);

    bool createWorkEntry(const WorkEntry& entry);

    std::vector<WorkEntry> getWorkEntries();

    bool updateWorkEntry(const WorkEntry& entry);

    bool deleteWorkEntry(int entryId);
};

#endif // WORK_ENTRY_SERVICE_H