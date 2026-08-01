#ifndef SETTINGS_SERVICE_H
#define SETTINGS_SERVICE_H

#include "../database/database_manager.h"
#include "../database/settings_model.h"

#include <vector>

class SettingsService
{
private:

    DatabaseManager& dbManager;

public:

    SettingsService(DatabaseManager& db);

    bool createSetting(const Setting& setting);

    std::vector<Setting> getSettings();

    bool updateSetting(const Setting& setting);

    bool deleteSetting(int settingId);

};

#endif