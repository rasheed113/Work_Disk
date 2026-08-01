#ifndef FINANCE_MODEL_H
#define FINANCE_MODEL_H

#include <string>

class FinanceEntry
{
public:
    int id;
    int userId;

    std::string type;
    double amount;
    std::string note;
    std::string entryDate;

    FinanceEntry();
};

#endif