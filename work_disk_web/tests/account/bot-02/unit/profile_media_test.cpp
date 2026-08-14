#include "../../../../src/account/bot-02/media/profile_media.h"

#include <cassert>

using work_disk::account::ProfileMediaReference;
using work_disk::account::ProfileMediaType;

int main() {
    ProfileMediaReference profilePicture{
        "media-001",
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        "media/ref/profile-001.jpg",
        "2026-08-14T17:00:00+05:00",
        "privacy-001",
        true
    };

    assert(
        profilePicture.type ==
        ProfileMediaType::PROFILE_PICTURE
    );

    assert(profilePicture.current);
    assert(profilePicture.profileId == "profile-001");
    assert(!profilePicture.mediaReference.empty());
    assert(!profilePicture.createdAt.empty());
    assert(!profilePicture.privacyReference.empty());

    ProfileMediaReference coverPicture{
        "media-002",
        "profile-001",
        ProfileMediaType::COVER_PICTURE,
        "media/ref/profile-001-cover.jpg",
        "2026-08-14T17:05:00+05:00",
        "privacy-001",
        true
    };

    assert(
        coverPicture.type ==
        ProfileMediaType::COVER_PICTURE
    );

    assert(coverPicture.current);

    return 0;
}
