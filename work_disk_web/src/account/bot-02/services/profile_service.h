#ifndef WORK_DISK_PROFILE_SERVICE_H
#define WORK_DISK_PROFILE_SERVICE_H

#include "../assembly/profile_assembly.h"
#include "../completion/profile_completion.h"
#include "../media/profile_media_repository.h"
#include "../repositories/profile_repository.h"
#include "../validators/profile_validator.h"

#include <string>

namespace work_disk::account {

class ProfileService {
public:
    ProfileService(
        ProfileRepository& profileRepository,
        ProfileMediaRepository& mediaRepository
    );

    ProfileAssembly assemble(
        const std::string& profileId,
        const ProfilePrivacyDecision& privacyDecision
    ) const;

private:
    ProfileRepository& profileRepository_;
    ProfileMediaRepository& mediaRepository_;
};

} // namespace work_disk::account

#endif
