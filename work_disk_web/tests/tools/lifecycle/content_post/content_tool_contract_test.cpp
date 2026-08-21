#include "../../../../src/tools/lifecycle/content_post/content_tool.h"
#include <cassert>

using namespace work_disk::tools::content_post;

namespace {
struct Authority final : ContentAuthority {
    bool allowed{true};
    int calls{0};
    bool may_create(const ContentCommand&) const override {
        return allowed;
    }
};

struct Provider final : ContentProvider {
    int calls{0};
    ContentResult create(const ContentCommand&) override {
        ++calls;
        return {ContentResultCode::Created, {"post", "opaque-post-1"}};
    }
};

ContentCommand valid_command() {
    return {"req-1", "auth-1", "scope-1", ContentKind::Post,
            "payload-1", "visibility-1", "idem-1"};
}
}

int main() {
    Authority authority;
    Provider provider;
    ContentTool tool(authority, provider);

    const auto created = tool.handle(valid_command());
    assert(created.code == ContentResultCode::Created);
    assert(provider.calls == 1);

    authority.allowed = false;
    const auto rejected = tool.handle(valid_command());
    assert(rejected.code == ContentResultCode::AuthorityRejected);
    assert(provider.calls == 1);

    authority.allowed = true;
    auto invalid = valid_command();
    invalid.creation_scope_reference.clear();
    const auto invalid_result = tool.handle(invalid);
    assert(invalid_result.code == ContentResultCode::InvalidRequest);
    assert(provider.calls == 1);

    return 0;
}
