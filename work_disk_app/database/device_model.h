#ifndef DEVICE_MODEL_H
#define DEVICE_MODEL_H

#include <string>

class Device
{
public:
    int id;
    int userId;

    std::string deviceName;
    std::string deviceId;
    std::string platform;

    std::string createdAt;

    Device();
};

#endif