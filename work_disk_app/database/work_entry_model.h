#ifndef WORK_ENTRY_MODEL_H
#define WORK_ENTRY_MODEL_H

#include <string>

class WorkEntry
{
public:
    int id;
    int userId;

    std::string date;
    std::string itemName;

    int quantity;

    double rate;
    double amount;

    std::string notes;

    std::string createdAt;
    std::string updatedAt;

    WorkEntry();
};

#endif // WORK_ENTRY_MODEL_H