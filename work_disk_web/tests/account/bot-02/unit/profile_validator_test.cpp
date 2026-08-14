#include "../../../../src/account/bot-02/validators/profile_validator.h"

#include <cassert>

using work_disk::account::Profile;
using work_disk::account::ProfileValidator;

int main() {
    Profile validProfile(
        "account-001",
        "profile-001",
        "Rasheed",
        "Male",
        "+92-300-0000000",
        "Personal bio",
        "Garment business"
    );

    const auto validResult =
        ProfileValidator::validate(validProfile);

    assert(validResult.valid);
    assert(validResult.errors.empty());

    Profile invalidProfile;

    const auto invalidResult =
        ProfileValidator::validate(invalidProfile);

    assert(!invalidResult.valid);
    assert(invalidResult.errors.size() == 7);

    return 0;
}
