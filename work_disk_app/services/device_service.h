#ifndef DEVICE_SERVICE_H
#define DEVICE_SERVICE_H

#include "../database/database_manager.h"
#include "../database/device_model.h"

#include <vector>

class DeviceService
{
private:
    DatabaseManager& dbManager;

public:
    DeviceService(DatabaseManager& db);

    bool createDevice(const Device& device);

    std::vector<Device> getDevices();

    bool updateDevice(const Device& device);

    bool deleteDevice(int deviceId);
};

#endif