#ifndef FINANCE_SERVICE_H
#define FINANCE_SERVICE_H

#include "../database/database_manager.h"
#include "../database/finance_model.h"

#include <vector>

class FinanceService
{
private:
    DatabaseManager& dbManager;

public:
    FinanceService(DatabaseManager& db);

    bool createFinance(const FinanceEntry& finance);

    std::vector<FinanceEntry> getFinanceEntries();

    bool updateFinance(const FinanceEntry& finance);

    bool deleteFinance(int financeId);
};

#endif