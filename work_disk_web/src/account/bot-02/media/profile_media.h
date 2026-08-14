#ifndef WORK_DISK_PROFILE_MEDIA_H
#define WORK_DISK_PROFILE_MEDIA_H

#include <string>

namespace work_disk::account {

enum class ProfileMediaType {
    PROFILE_PICTURE,
    COVER_PICTURE
};

struct ProfileMediaReference {
    std::string mediaId;
    std::string profileId;
    ProfileMediaType type;
    std::string mediaReference;
    std::string createdAt;
    std::string privacyReference;
    bool current = false;
};

} // namespace work_disk::account

#endif
