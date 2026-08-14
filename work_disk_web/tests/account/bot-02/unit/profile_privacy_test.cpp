#include "../../../../src/account/bot-02/privacy/profile_privacy.h"

#include <cassert>

using work_disk::account::ProfilePrivacyDecision;
using work_disk::account::ProfileVisibility;

int main() {
    ProfilePrivacyDecision decision{
        "profile-001",
        ProfileVisibility::FRIENDS_AND_FOLLOWERS,
        true
    };

    assert(decision.profileId == "profile-001");
    assert(
        decision.visibility ==
        ProfileVisibility::FRIENDS_AND_FOLLOWERS
    );
    assert(decision.authorised);

    return 0;
}
