#include "settings_service.h"

SettingsService::SettingsService(DatabaseManager& db)
    : dbManager(db)
{

}

bool SettingsService::createSetting(const Setting& setting)
{
    return dbManager.insertSetting(setting);
}

std::vector<Setting> SettingsService::getSettings()
{
    return dbManager.getAllSettings();
}

bool SettingsService::updateSetting(const Setting& setting)
{
    return dbManager.updateSetting(setting);
}

bool SettingsService::deleteSetting(int settingId)
{
    return dbManager.deleteSetting(settingId);
}