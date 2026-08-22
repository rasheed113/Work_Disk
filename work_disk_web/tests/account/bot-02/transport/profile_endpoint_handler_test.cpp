#include "../../../src/account/bot-02/transport/profile_endpoint_handler.h"

#include <cassert>

using namespace work_disk::account;

namespace {

class StubProfileService : public ProfileService {
public:
    StubProfileService(ProfileRepository& profiles, ProfileMediaRepository& media)
        : ProfileService(profiles, media) {}
};

} // namespace

// Contract-level checks for request validation. Full authoritative assembly
// tests remain owned by BOT-02 service tests; transport tests must not invent
// domain fixtures.
void profile_endpoint_rejects_missing_request_id();
void profile_endpoint_rejects_missing_profile_id();
