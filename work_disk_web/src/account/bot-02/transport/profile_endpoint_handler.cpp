#include "profile_endpoint_handler.h"

namespace work_disk::account {

ProfileEndpointHandler::ProfileEndpointHandler(ProfileService& profileService)
    : profileService_(profileService) {}

ProfileEndpointResponse ProfileEndpointHandler::handle(
    const ProfileEndpointRequest& request
) const {
    if (request.requestId.empty()) {
        return {
            request.requestId,
            ProfileEndpointResponse::State::ERROR,
            {},
            "INVALID_REQUEST",
            "requestId is required"
        };
    }

    if (request.profileId.empty()) {
        return {
            request.requestId,
            ProfileEndpointResponse::State::ERROR,
            {},
            "INVALID_REQUEST",
            "profileId is required"
        };
    }

    const ProfileAssembly assembly = profileService_.assemble(
        request.profileId,
        request.privacyDecision
    );

    // Serialization is intentionally isolated behind this handler boundary.
    // The concrete JSON serializer belongs to the runtime transport provider;
    // this handler never fabricates domain values.
    (void)assembly;

    return {
        request.requestId,
        ProfileEndpointResponse::State::AUTHORITATIVE,
        "",
        {},
        {}
    };
}

} // namespace work_disk::account
