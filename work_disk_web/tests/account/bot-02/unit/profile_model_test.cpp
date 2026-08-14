#include "../../../../src/account/bot-02/models/profile_model.h"

#include <cassert>

using work_disk::account::Profile;

int main() {
    Profile profile(
        "account-001",
        "profile-001",
        "Rasheed",
        "Male",
        "+92-300-0000000",
        "Personal bio",
        "Garment business"
    );

    assert(profile.exists());

    assert(profile.accountId() == "account-001");
    assert(profile.profileId() == "profile-001");
    assert(profile.displayName() == "Rasheed");
    assert(profile.gender() == "Male");
    assert(profile.mobileContactNumber() == "+92-300-0000000");
    assert(profile.bio() == "Personal bio");
    assert(profile.workBusinessDescription() == "Garment business");

    profile.setDisplayName("Rasheed Gull");
    profile.setGender("Male");
    profile.setMobileContactNumber("+92-301-1111111");
    profile.setBio("Updated bio");
    profile.setWorkBusinessDescription("Updated business description");

    assert(profile.displayName() == "Rasheed Gull");
    assert(profile.gender() == "Male");
    assert(profile.mobileContactNumber() == "+92-301-1111111");
    assert(profile.bio() == "Updated bio");
    assert(profile.workBusinessDescription() == "Updated business description");

    Profile emptyProfile;

    assert(!emptyProfile.exists());
    assert(emptyProfile.accountId().empty());
    assert(emptyProfile.profileId().empty());

    return 0;
}
