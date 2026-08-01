#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <sqlite3.h>
#include <string>
#include <vector>

#include "user_model.h"
#include "work_entry_model.h"
#include "settings_model.h"
#include "finance_model.h"
#include "diary_model.h"
#include "device_model.h"

class DatabaseManager
{
private:
    sqlite3* db;

public:
    DatabaseManager();
    ~DatabaseManager();

    bool initializeDatabase();
    bool createTables();

    // Connection Status
bool isConnected() const;

// SQL Utilities
bool executeSQL(const std::string& sql);

// Transaction Control
bool beginTransaction();
bool commitTransaction();
bool rollbackTransaction();

// Error Handling
std::string getLastError() const;

    bool insertUser(const User& user);

    std::vector<User> getAllUsers();

    bool updateUser(const User& user);

    bool deleteUser(int userId);

    bool insertWorkEntry(const WorkEntry& entry);

std::vector<WorkEntry> getAllWorkEntries();

bool updateWorkEntry(const WorkEntry& entry);

bool deleteWorkEntry(int entryId);

// Settings CRUD
bool insertSetting(const Setting& setting);

std::vector<Setting> getAllSettings();

bool updateSetting(const Setting& setting);

bool deleteSetting(int settingId);

// Finance CRUD

bool insertFinance(const FinanceEntry& finance);

std::vector<FinanceEntry> getAllFinance();

bool updateFinance(const FinanceEntry& finance);

bool deleteFinance(int financeId);

// Diary CRUD

bool insertDiaryEntry(const DiaryEntry& diary);

std::vector<DiaryEntry> getAllDiaryEntries();

bool updateDiaryEntry(const DiaryEntry& diary);

bool deleteDiaryEntry(int diaryId);

// Device CRUD

bool insertDevice(const Device& device);

std::vector<Device> getAllDevices();

bool updateDevice(const Device& device);

bool deleteDevice(int deviceId);

    sqlite3* getDatabase();
};

#endif