#ifndef WORK_DISK_PROFILE_MEDIA_REPOSITORY_H
#define WORK_DISK_PROFILE_MEDIA_REPOSITORY_H

#include "profile_media.h"

#include <string>
#include <vector>

namespace work_disk::account {

class ProfileMediaRepository {
public:
    bool add(const ProfileMediaReference& media);

    ProfileMediaReference current(
        const std::string& profileId,
        ProfileMediaType type
    ) const;

    std::vector<ProfileMediaReference> history(
        const std::string& profileId,
        ProfileMediaType type
    ) const;

    bool replaceCurrent(
        const std::string& profileId,
        ProfileMediaType type,
        const ProfileMediaReference& replacement
    );

private:
    std::vector<ProfileMediaReference> media_;
};

} // namespace work_disk::account

#endif
