#include "../../../../src/account/bot-02/media/profile_media_repository.h"

#include <cassert>

using work_disk::account::ProfileMediaReference;
using work_disk::account::ProfileMediaRepository;
using work_disk::account::ProfileMediaType;

int main() {
    ProfileMediaRepository repository;

    ProfileMediaReference first{
        "media-001",
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        "media/profile-001-v1.jpg",
        "2026-08-14T17:00:00+05:00",
        "privacy-001",
        true
    };

    assert(repository.add(first));

    const auto firstCurrent =
        repository.current(
            "profile-001",
            ProfileMediaType::PROFILE_PICTURE
        );

    assert(firstCurrent.mediaId == "media-001");
    assert(firstCurrent.current);

    ProfileMediaReference replacement{
        "media-002",
        "profile-001",
        ProfileMediaType::PROFILE_PICTURE,
        "media/profile-001-v2.jpg",
        "2026-08-14T17:10:00+05:00",
        "privacy-001",
        true
    };

    assert(
        repository.replaceCurrent(
            "profile-001",
            ProfileMediaType::PROFILE_PICTURE,
            replacement
        )
    );

    const auto current =
        repository.current(
            "profile-001",
            ProfileMediaType::PROFILE_PICTURE
        );

    assert(current.mediaId == "media-002");
    assert(current.current);

    const auto history =
        repository.history(
            "profile-001",
            ProfileMediaType::PROFILE_PICTURE
        );

    assert(history.size() == 1);
    assert(history[0].mediaId == "media-001");
    assert(!history[0].current);

    // Old media still exists: replacement is NOT deletion.
    assert(history[0].mediaReference ==
           "media/profile-001-v1.jpg");

    return 0;
}
