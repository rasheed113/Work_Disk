#include "../../../../src/account/bot-02/services/profile_service.h"

#include <cassert>

using work_disk::account::Profile;
using work_disk::account::ProfileAssembly;
using work_disk::account::ProfileMediaReference;
using work_disk::account::ProfileMediaRepository;
using work_disk::account::ProfileMediaType;
using work_disk::account::ProfilePrivacyDecision;
using work_disk::account::ProfileRepository;
using work_disk::account::ProfileService;
using work_disk::account::ProfileVisibility;

int main() {
    ProfileRepository profileRepository;
    ProfileMediaRepository mediaRepository;

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

    assert(mediaRepository.add({
        "media-001",
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        "media/profile-001-v1.jpg",
        "2026-08-14T17:00:00+05:00",
        "privacy-001",
        true
    }));

    assert(mediaRepository.add({
        "media-002",
        "profile-001",
        ProfileMediaType::COVER_PICTURE,
        "media/profile-001-cover-v1.jpg",
        "2026-08-14T17:05:00+05:00",
        "privacy-001",
        true
    }));

    assert(mediaRepository.replaceCurrent(
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        {
            "media-003",
            "profile-001",
            ProfileMediaType::PROFILE_PICTURE,
            "media/profile-001-v2.jpg",
            "2026-08-14T17:10:00+05:00",
            "privacy-001",
            true
        }
    ));

    ProfileService service(
        profileRepository,
        mediaRepository
    );

    ProfilePrivacyDecision privacy{
        "profile-001",
        ProfileVisibility::GLOBAL,
        true
    };

    const ProfileAssembly assembly =
        service.assemble(
            "profile-001",
            privacy
        );

    assert(
        assembly.profile.profileId() ==
        "profile-001"
    );

    assert(
        assembly.currentProfilePicture.mediaId ==
        "media-003"
    );

    assert(
        assembly.currentProfilePicture.current
    );

    assert(
        assembly.currentCoverPicture.mediaId ==
        "media-002"
    );

    assert(
        assembly.historicalProfileMedia.size() ==
        1
    );

    assert(
        assembly.historicalProfileMedia[0].mediaId ==
        "media-001"
    );

    assert(
        !assembly.historicalProfileMedia[0].current
    );

    assert(
        assembly.privacyDecision.authorised
    );

    assert(
        assembly.privacyDecision.visibility ==
        ProfileVisibility::GLOBAL
    );

    return 0;
}
