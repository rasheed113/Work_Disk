#include "profile_service.h"

namespace work_disk::account {

ProfileService::ProfileService(
    ProfileRepository& profileRepository,
    ProfileMediaRepository& mediaRepository
)
    : profileRepository_(profileRepository),
      mediaRepository_(mediaRepository) {}

ProfileAssembly ProfileService::assemble(
    const std::string& profileId,
    const ProfilePrivacyDecision& privacyDecision
) const {
    ProfileAssembly assembly;

    assembly.profile =
        profileRepository_.findById(profileId);

    assembly.completion =
        ProfileCompletion::evaluate(
            assembly.profile
        );

    assembly.currentProfilePicture =
        mediaRepository_.current(
            profileId,
            ProfileMediaType::PROFILE_PICTURE
        );

    assembly.currentCoverPicture =
        mediaRepository_.current(
            profileId,
            ProfileMediaType::COVER_PICTURE
        );

    assembly.historicalProfileMedia =
        mediaRepository_.history(
            profileId,
            ProfileMediaType::PROFILE_PICTURE
        );

    const auto coverHistory =
        mediaRepository_.history(
            profileId,
            ProfileMediaType::COVER_PICTURE
        );

    assembly.historicalProfileMedia.insert(
        assembly.historicalProfileMedia.end(),
        coverHistory.begin(),
        coverHistory.end()
    );

    assembly.privacyDecision =
        privacyDecision;

    return assembly;
}

} // namespace work_disk::account
