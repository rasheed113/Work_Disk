#include "finance_service.h"

FinanceService::FinanceService(DatabaseManager& db)
    : dbManager(db)
{
}

bool FinanceService::createFinance(const FinanceEntry& finance)
{
    return dbManager.insertFinance(finance);
}

std::vector<FinanceEntry> FinanceService::getFinanceEntries()
{
    return dbManager.getAllFinance();
}

bool FinanceService::updateFinance(const FinanceEntry& finance)
{
    return dbManager.updateFinance(finance);
}

bool FinanceService::deleteFinance(int financeId)
{
    return dbManager.deleteFinance(financeId);
}