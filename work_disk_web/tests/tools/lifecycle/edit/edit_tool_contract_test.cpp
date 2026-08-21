#include "../../../src/tools/lifecycle/edit/edit_tool.h"
#include <cassert>

using namespace work_disk::tools::edit;

namespace {
struct Authority final : EditAuthority {
    bool allow{true};
    bool authorised(const EditCommand&) const override { return allow; }
};

struct Store final : EditStore {
    EditResult begin_result{EditResultCode::Edited, 1};
    EditResult complete_result{EditResultCode::Edited, 2};
    int begin_calls{0};
    int complete_calls{0};
    EditResult begin(const EditCommand&) override { ++begin_calls; return begin_result; }
    EditResult complete(const EditCommand&, const EditResult&) override { ++complete_calls; return complete_result; }
};

struct Executor final : EditExecutor {
    EditResult result{EditResultCode::Edited, 1};
    int calls{0};
    EditResult execute(const EditCommand&) override { ++calls; return result; }
};

EditCommand command() {
    return {"request-1", "entry", "entry-1", "authority-1", "pieces", "122", 1, false};
}
}

int main() {
    Authority authority;
    Store store;
    Executor executor;
    EditTool tool(authority, store, executor);

    const auto ok = tool.handle(command());
    assert(ok.code == EditResultCode::Edited);
    assert(executor.calls == 1);
    assert(store.begin_calls == 1);
    assert(store.complete_calls == 1);

    authority.allow = false;
    const auto denied = tool.handle(command());
    assert(denied.code == EditResultCode::AuthorityRejected);
    assert(executor.calls == 1);

    authority.allow = true;
    store.begin_result = {EditResultCode::VersionConflict, 3};
    const auto stale = tool.handle(command());
    assert(stale.code == EditResultCode::VersionConflict);
    assert(executor.calls == 1);

    store.begin_result = {EditResultCode::NoOp, 4};
    const auto noop = tool.handle(command());
    assert(noop.code == EditResultCode::NoOp);
    assert(executor.calls == 1);

    const EditCommand invalid{"", "entry", "entry-1", "authority-1", "pieces", "122", 1, false};
    assert(tool.handle(invalid).code == EditResultCode::InvalidRequest);

    return 0;
}
