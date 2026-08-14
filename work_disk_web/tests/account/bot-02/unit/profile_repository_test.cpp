#include "../../../../src/account/bot-02/repositories/profile_repository.h"

#include <cassert>

using work_disk::account::Profile;
using work_disk::account::ProfileRepository;

int main() {
    ProfileRepository repository;

    Profile profile(
        "account-001",
        "profile-001",
        "Rasheed",
        "Male",
        "+92-300-0000000",
        "Personal bio",
        "Garment business"
    );

    assert(repository.save(profile));

    assert(repository.exists("profile-001"));
    assert(!repository.exists("profile-missing"));

    const Profile byId = repository.findById("profile-001");

    assert(byId.exists());
    assert(byId.profileId() == "profile-001");
    assert(byId.accountId() == "account-001");
    assert(byId.displayName() == "Rasheed");

    const Profile byAccount =
        repository.findByAccountId("account-001");

    assert(byAccount.exists());
    assert(byAccount.profileId() == "profile-001");

    const Profile missingById =
        repository.findById("profile-missing");

    assert(!missingById.exists());

    const Profile missingByAccount =
        repository.findByAccountId("account-missing");

    assert(!missingByAccount.exists());

    Profile invalidProfile(
        "",
        "",
        "Invalid",
        "",
        "",
        "",
        ""
    );

    assert(!repository.save(invalidProfile));

    return 0;
}
