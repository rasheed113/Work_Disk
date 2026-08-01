#ifndef DIARY_MODEL_H
#define DIARY_MODEL_H

#include <string>

class DiaryEntry
{
public:
    int id;
    int userId;

    std::string title;
    std::string content;
    std::string mood;

    std::string createdAt;
    std::string updatedAt;

    DiaryEntry();
};

#endif