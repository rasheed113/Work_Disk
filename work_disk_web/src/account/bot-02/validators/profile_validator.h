#ifndef WORK_DISK_PROFILE_VALIDATOR_H
#define WORK_DISK_PROFILE_VALIDATOR_H

#include "../models/profile_model.h"

#include <string>
#include <vector>

namespace work_disk::account {

struct ProfileValidationResult {
    bool valid = false;
    std::vector<std::string> errors;
};

class ProfileValidator {
public:
    static ProfileValidationResult validate(
        const Profile& profile
    );
};

} // namespace work_disk::account

#endif
