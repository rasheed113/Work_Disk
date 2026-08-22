#ifndef WORK_DISK_PROFILE_ENDPOINT_HANDLER_H
#define WORK_DISK_PROFILE_ENDPOINT_HANDLER_H

#include "../services/profile_service.h"
#include <string>

namespace work_disk::account {

struct ProfileEndpointRequest {
    std::string requestId;
    std::string profileId;
    ProfilePrivacyDecision privacyDecision;
};

struct ProfileEndpointResponse {
    std::string requestId;
    enum class State { AUTHORITATIVE, EMPTY, ERROR } state;
    std::string serializedPayload;
    std::string errorCode;
    std::string errorMessage;
};

class ProfileEndpointHandler {
public:
    explicit ProfileEndpointHandler(ProfileService& profileService);

    ProfileEndpointResponse handle(
        const ProfileEndpointRequest& request
    ) const;

private:
    ProfileService& profileService_;
};

} // namespace work_disk::account

#endif
