#include "device_service.h"

DeviceService::DeviceService(DatabaseManager& db)
    : dbManager(db)
{
}

bool DeviceService::createDevice(const Device& device)
{
    return dbManager.insertDevice(device);
}

std::vector<Device> DeviceService::getDevices()
{
    return dbManager.getAllDevices();
}

bool DeviceService::updateDevice(const Device& device)
{
    return dbManager.updateDevice(device);
}

bool DeviceService::deleteDevice(int deviceId)
{
    return dbManager.deleteDevice(deviceId);
}