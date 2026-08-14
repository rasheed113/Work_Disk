#ifndef WORK_DISK_PROFILE_ASSEMBLY_H
#define WORK_DISK_PROFILE_ASSEMBLY_H

#include "../completion/profile_completion.h"
#include "../media/profile_media.h"
#include "../models/profile_model.h"
#include "../privacy/profile_privacy.h"

#include <vector>

namespace work_disk::account {

struct ProfileAssembly {
    Profile profile;

    ProfileCompletionResult completion;

    ProfileMediaReference currentProfilePicture;
    ProfileMediaReference currentCoverPicture;

    std::vector<ProfileMediaReference>
        historicalProfileMedia;

    ProfilePrivacyDecision privacyDecision;
};

} // namespace work_disk::account

#endif
