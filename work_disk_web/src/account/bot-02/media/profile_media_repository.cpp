#include "profile_media_repository.h"

namespace work_disk::account {

bool ProfileMediaRepository::add(
    const ProfileMediaReference& media
) {
    if (media.mediaId.empty() ||
        media.profileId.empty() ||
        media.mediaReference.empty()) {
        return false;
    }

    media_.push_back(media);
    return true;
}

ProfileMediaReference ProfileMediaRepository::current(
    const std::string& profileId,
    ProfileMediaType type
) const {
    for (const auto& media : media_) {
        if (media.profileId == profileId &&
            media.type == type &&
            media.current) {
            return media;
        }
    }

    return {};
}

std::vector<ProfileMediaReference>
ProfileMediaRepository::history(
    const std::string& profileId,
    ProfileMediaType type
) const {
    std::vector<ProfileMediaReference> result;

    for (const auto& media : media_) {
        if (media.profileId == profileId &&
            media.type == type &&
            !media.current) {
            result.push_back(media);
        }
    }

    return result;
}

bool ProfileMediaRepository::replaceCurrent(
    const std::string& profileId,
    ProfileMediaType type,
    const ProfileMediaReference& replacement
) {
    if (replacement.mediaId.empty() ||
        replacement.profileId != profileId ||
        replacement.type != type ||
        replacement.mediaReference.empty()) {
        return false;
    }

    for (auto& media : media_) {
        if (media.profileId == profileId &&
            media.type == type &&
            media.current) {
            media.current = false;
        }
    }

    media_.push_back(replacement);

    return true;
}

} // namespace work_disk::account
