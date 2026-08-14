#include "../../../src/account/bot-02/services/profile_service.h"

#include <cassert>

using namespace work_disk::account;

int main() {
    ProfileRepository profileRepository;
    ProfileMediaRepository mediaRepository;

    // ------------------------------------------------------------
    // 1. Create an authoritative profile record
    // ------------------------------------------------------------

    Profile profile(
        "account-001",
        "profile-001",
        "Rasheed",
        "Male",
        "+92-300-0000000",
        "Personal bio",
        "Garment business"
    );

    assert(profileRepository.save(profile));

    // ------------------------------------------------------------
    // 2. Establish current profile media
    // ------------------------------------------------------------

    assert(mediaRepository.add({
        "media-profile-v1",
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        "media/profile-v1.jpg",
        "2026-08-14T10:00:00+05:00",
        "privacy-001",
        true
    }));

    assert(mediaRepository.add({
        "media-cover-v1",
        "profile-001",
        ProfileMediaType::COVER_PICTURE,
        "media/cover-v1.jpg",
        "2026-08-14T10:01:00+05:00",
        "privacy-001",
        true
    }));

    // ------------------------------------------------------------
    // 3. Replace profile picture
    //    Replacement must preserve previous media as history.
    // ------------------------------------------------------------

    assert(mediaRepository.replaceCurrent(
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        {
            "media-profile-v2",
            "profile-001",
            ProfileMediaType::PROFILE_PICTURE,
            "media/profile-v2.jpg",
            "2026-08-14T10:02:00+05:00",
            "privacy-001",
            true
        }
    ));

    // ------------------------------------------------------------
    // 4. Supply an already-authorised privacy decision.
    //    BOT-02 does not calculate this decision.
    // ------------------------------------------------------------

    ProfilePrivacyDecision privacyDecision{
        "profile-001",
        ProfileVisibility::GLOBAL,
        true
    };

    // ------------------------------------------------------------
    // 5. Assemble the complete profile.
    // ------------------------------------------------------------

    ProfileService service(
        profileRepository,
        mediaRepository
    );

    const ProfileAssembly assembly =
        service.assemble(
            "profile-001",
            privacyDecision
        );

    // ------------------------------------------------------------
    // 6. Core profile
    // ------------------------------------------------------------

    assert(
        assembly.profile.accountId() ==
        "account-001"
    );

    assert(
        assembly.profile.profileId() ==
        "profile-001"
    );

    assert(
        assembly.profile.displayName() ==
        "Rasheed"
    );

    // ------------------------------------------------------------
    // 7. Completion
    // ------------------------------------------------------------

    assert(
        assembly.completion.percentage ==
        100
    );

    assert(
        assembly.completion.state ==
        ProfileCompletionState::COMPLETE
    );

    assert(
        assembly.completion.missingRequirements.empty()
    );

    assert(
        assembly.completion.suggestions.empty()
    );

    // ------------------------------------------------------------
    // 8. Current media
    // ------------------------------------------------------------

    assert(
        assembly.currentProfilePicture.mediaId ==
        "media-profile-v2"
    );

    assert(
        assembly.currentProfilePicture.current
    );

    assert(
        assembly.currentCoverPicture.mediaId ==
        "media-cover-v1"
    );

    assert(
        assembly.currentCoverPicture.current
    );

    // ------------------------------------------------------------
    // 9. Historical media
    // ------------------------------------------------------------

    assert(
        assembly.historicalProfileMedia.size() ==
        1
    );

    assert(
        assembly.historicalProfileMedia[0].mediaId ==
        "media-profile-v1"
    );

    assert(
        !assembly.historicalProfileMedia[0].current
    );

    // ------------------------------------------------------------
    // 10. Privacy reference
    // ------------------------------------------------------------

    assert(
        assembly.privacyDecision.profileId ==
        "profile-001"
    );

    assert(
        assembly.privacyDecision.visibility ==
        ProfileVisibility::GLOBAL
    );

    assert(
        assembly.privacyDecision.authorised
    );

    // ------------------------------------------------------------
    // 11. Nonexistent profile must not accidentally assemble
    //    another profile.
    // ------------------------------------------------------------

    const ProfileAssembly missing =
        service.assemble(
            "profile-does-not-exist",
            {
                "profile-does-not-exist",
                ProfileVisibility::ONLY_ME,
                false
            }
        );

    assert(
        missing.profile.profileId().empty()
    );

    assert(
        !missing.privacyDecision.authorised
    );

    return 0;
}
