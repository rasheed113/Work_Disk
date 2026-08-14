#ifndef WORK_DISK_PROFILE_COMPLETION_H
#define WORK_DISK_PROFILE_COMPLETION_H

#include "../models/profile_model.h"

#include <string>
#include <vector>

namespace work_disk::account {

enum class ProfileCompletionState {
    INCOMPLETE,
    COMPLETE
};

struct ProfileCompletionResult {
    int percentage = 0;
    ProfileCompletionState state =
        ProfileCompletionState::INCOMPLETE;

    std::vector<std::string> missingRequirements;
    std::vector<std::string> suggestions;
};

class ProfileCompletion {
public:
    static ProfileCompletionResult evaluate(
        const Profile& profile
    );
};

} // namespace work_disk::account

#endif
