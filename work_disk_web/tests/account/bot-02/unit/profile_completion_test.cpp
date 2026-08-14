#include "../../../../src/account/bot-02/completion/profile_completion.h"

#include <cassert>

using work_disk::account::Profile;
using work_disk::account::ProfileCompletion;
using work_disk::account::ProfileCompletionState;

int main() {
    Profile emptyProfile(
        "account-001",
        "profile-001",
        "",
        "",
        "",
        "",
        ""
    );

    const auto emptyResult =
        ProfileCompletion::evaluate(emptyProfile);

    assert(emptyResult.percentage == 0);
    assert(
        emptyResult.state ==
        ProfileCompletionState::INCOMPLETE
    );

    assert(emptyResult.missingRequirements.size() == 5);
    assert(emptyResult.suggestions.size() == 5);

    Profile halfProfile(
        "account-001",
        "profile-001",
        "Rasheed",
        "Male",
        "",
        "",
        ""
    );

    const auto halfResult =
        ProfileCompletion::evaluate(halfProfile);

    assert(halfResult.percentage == 40);
    assert(
        halfResult.state ==
        ProfileCompletionState::INCOMPLETE
    );

    assert(halfResult.missingRequirements.size() == 3);
    assert(halfResult.suggestions.size() == 3);

    Profile completeProfile(
        "account-001",
        "profile-001",
        "Rasheed",
        "Male",
        "+92-300-0000000",
        "Personal bio",
        "Garment business"
    );

    const auto completeResult =
        ProfileCompletion::evaluate(completeProfile);

    assert(completeResult.percentage == 100);
    assert(
        completeResult.state ==
        ProfileCompletionState::COMPLETE
    );

    assert(completeResult.missingRequirements.empty());
    assert(completeResult.suggestions.empty());

    return 0;
}
