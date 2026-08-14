#include "../../../../src/account/bot-02/assembly/profile_assembly.h"

#include <cassert>

using work_disk::account::Profile;
using work_disk::account::ProfileAssembly;
using work_disk::account::ProfileCompletionState;
using work_disk::account::ProfileMediaType;

int main() {
    ProfileAssembly assembly;

    assembly.profile = Profile(
        "account-001",
        "profile-001",
        "Rasheed",
        "Male",
        "+92-300-0000000",
        "Personal bio",
        "Garment business"
    );

    assembly.completion.percentage = 100;
    assembly.completion.state =
        ProfileCompletionState::COMPLETE;

    assembly.currentProfilePicture = {
        "media-001",
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        "media/profile-001.jpg",
        "2026-08-14T17:00:00+05:00",
        "privacy-001",
        true
    };

    assembly.currentCoverPicture = {
        "media-002",
        "profile-001",
        ProfileMediaType::COVER_PICTURE,
        "media/profile-001-cover.jpg",
        "2026-08-14T17:05:00+05:00",
        "privacy-001",
        true
    };

    assembly.historicalProfileMedia.push_back({
        "media-000",
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        "media/profile-001-old.jpg",
        "2026-08-10T17:00:00+05:00",
        "privacy-001",
        false
    });

    assert(assembly.profile.profileId() == "profile-001");
    assert(assembly.profile.accountId() == "account-001");

    assert(assembly.completion.percentage == 100);

    assert(
        assembly.currentProfilePicture.type ==
        ProfileMediaType::PROFILE_PICTURE
    );

    assert(
        assembly.currentProfilePicture.current
    );

    assert(
        assembly.currentCoverPicture.type ==
        ProfileMediaType::COVER_PICTURE
    );

    assert(
        assembly.currentCoverPicture.current
    );

    assert(
        assembly.historicalProfileMedia.size() == 1
    );

    assert(
        !assembly.historicalProfileMedia[0].current
    );

    return 0;
}
