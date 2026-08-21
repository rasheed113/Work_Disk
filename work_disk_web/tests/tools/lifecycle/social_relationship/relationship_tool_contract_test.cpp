#include "../../../../src/tools/lifecycle/social_relationship/relationship_tool.h"
#include <cassert>

using namespace work_disk::tools::social_relationship;

namespace {
struct Authority final : RelationshipAuthority {
    bool allowed{true};
    bool may_apply(const RelationshipCommand&) const override { return allowed; }
};
struct Provider final : RelationshipProvider {
    int calls{0};
    RelationshipResult apply(const RelationshipCommand&) override {
        ++calls;
        return {RelationshipResultCode::Applied, "opaque-relationship"};
    }
};
RelationshipCommand command() {
    return {"req", "auth", "scope", "actor", "subject",
            RelationshipOperation::Follow, "idem", "v1"};
}
}

int main() {
    Authority authority;
    Provider provider;
    RelationshipTool tool(authority, provider);

    auto applied = tool.handle(command());
    assert(applied.code == RelationshipResultCode::Applied);
    assert(provider.calls == 1);

    authority.allowed = false;
    auto rejected = tool.handle(command());
    assert(rejected.code == RelationshipResultCode::AuthorityRejected);
    assert(provider.calls == 1);

    authority.allowed = true;
    auto invalid = command();
    invalid.actor_reference = invalid.subject_reference;
    auto invalid_result = tool.handle(invalid);
    assert(invalid_result.code == RelationshipResultCode::InvalidRequest);
    assert(provider.calls == 1);

    return 0;
}
