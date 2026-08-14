#include "profile_completion.h"

namespace work_disk::account {

ProfileCompletionResult ProfileCompletion::evaluate(
    const Profile& profile
) {
    ProfileCompletionResult result;

    struct Requirement {
        const char* name;
        const char* suggestion;
        bool complete;
    };

    const Requirement requirements[] = {
        {
            "display_name",
            "Add your profile name.",
            !profile.displayName().empty()
        },
        {
            "gender",
            "Add your gender.",
            !profile.gender().empty()
        },
        {
            "mobile_contact_number",
            "Add your mobile contact number.",
            !profile.mobileContactNumber().empty()
        },
        {
            "bio",
            "Add a short bio.",
            !profile.bio().empty()
        },
        {
            "work_business_description",
            "Add your work or business description.",
            !profile.workBusinessDescription().empty()
        }
    };

    constexpr int requirementCount =
        sizeof(requirements) / sizeof(requirements[0]);

    int completedCount = 0;

    for (const auto& requirement : requirements) {
        if (requirement.complete) {
            ++completedCount;
        } else {
            result.missingRequirements.emplace_back(
                requirement.name
            );

            result.suggestions.emplace_back(
                requirement.suggestion
            );
        }
    }

    if (requirementCount > 0) {
        result.percentage =
            (completedCount * 100) / requirementCount;
    }

    if (result.percentage == 100) {
        result.state = ProfileCompletionState::COMPLETE;
    }

    return result;
}

} // namespace work_disk::account
