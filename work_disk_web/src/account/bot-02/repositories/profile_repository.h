#ifndef WORK_DISK_PROFILE_REPOSITORY_H
#define WORK_DISK_PROFILE_REPOSITORY_H

#include "../models/profile_model.h"

#include <string>
#include <unordered_map>

namespace work_disk::account {

class ProfileRepository {
public:
    bool save(const Profile& profile);

    bool exists(const std::string& profileId) const;

    Profile findById(const std::string& profileId) const;

    Profile findByAccountId(const std::string& accountId) const;

private:
    std::unordered_map<std::string, Profile> profiles_;
};

} // namespace work_disk::account

#endif
