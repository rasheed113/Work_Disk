#ifndef SETTINGS_MODEL_H
#define SETTINGS_MODEL_H

#include <string>

class Setting
{
public:
    int id;
    std::string key;
    std::string value;

    Setting();
};

#endif