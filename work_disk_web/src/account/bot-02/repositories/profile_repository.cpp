#include "profile_repository.h"

namespace work_disk::account {

bool ProfileRepository::save(const Profile& profile) {
    if (profile.profileId().empty() || profile.accountId().empty()) {
        return false;
    }

    profiles_[profile.profileId()] = profile;
    return true;
}

bool ProfileRepository::exists(const std::string& profileId) const {
    return profiles_.find(profileId) != profiles_.end();
}

Profile ProfileRepository::findById(const std::string& profileId) const {
    const auto it = profiles_.find(profileId);

    if (it == profiles_.end()) {
        return {};
    }

    return it->second;
}

Profile ProfileRepository::findByAccountId(
    const std::string& accountId
) const {
    for (const auto& [profileId, profile] : profiles_) {
        if (profile.accountId() == accountId) {
            return profile;
        }
    }

    return {};
}

} // namespace work_disk::account
