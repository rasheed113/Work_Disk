#ifndef WORK_DISK_PROFILE_PRIVACY_H
#define WORK_DISK_PROFILE_PRIVACY_H

#include <string>

namespace work_disk::account {

enum class ProfileVisibility {
    ONLY_ME,
    FRIENDS_AND_FOLLOWERS,
    GLOBAL
};

struct ProfilePrivacyDecision {
    std::string profileId;
    ProfileVisibility visibility;
    bool authorised = false;
};

} // namespace work_disk::account

#endif
