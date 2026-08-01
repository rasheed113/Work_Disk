#include "finance_model.h"

FinanceEntry::FinanceEntry()
{
    id = 0;
    userId = 0;

    type = "Expense";
    amount = 0.0;
    note = "";
    entryDate = "";
}