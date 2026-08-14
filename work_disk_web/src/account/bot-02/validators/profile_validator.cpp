#include "profile_validator.h"

namespace work_disk::account {

ProfileValidationResult ProfileValidator::validate(
    const Profile& profile
) {
    ProfileValidationResult result;

    if (profile.accountId().empty()) {
        result.errors.emplace_back(
            "Account ID is required."
        );
    }

    if (profile.profileId().empty()) {
        result.errors.emplace_back(
            "Profile ID is required."
        );
    }

    if (profile.displayName().empty()) {
        result.errors.emplace_back(
            "Display name is required."
        );
    }

    if (profile.gender().empty()) {
        result.errors.emplace_back(
            "Gender is required."
        );
    }

    if (profile.mobileContactNumber().empty()) {
        result.errors.emplace_back(
            "Mobile contact number is required."
        );
    }

    if (profile.bio().empty()) {
        result.errors.emplace_back(
            "Bio is required."
        );
    }

    if (profile.workBusinessDescription().empty()) {
        result.errors.emplace_back(
            "Work/business description is required."
        );
    }

    result.valid = result.errors.empty();

    return result;
}

} // namespace work_disk::account
