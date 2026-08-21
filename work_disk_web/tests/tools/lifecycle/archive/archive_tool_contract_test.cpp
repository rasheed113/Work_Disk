#include "../../../src/tools/lifecycle/archive/archive_tool.h"
#include <cassert>

using namespace work_disk::tools::archive;

namespace {
struct Authority final : ArchiveAuthority {
    bool allow{true};
    bool authorised(const ArchiveCommand&) const override { return allow; }
};

struct Store final : ArchiveStore {
    ArchiveResult begin_result{ArchiveResultCode::Archived, 1};
    ArchiveResult complete_result{ArchiveResultCode::Archived, 2};
    int begin_calls{0};
    int complete_calls{0};
    ArchiveResult begin(const ArchiveCommand&) override { ++begin_calls; return begin_result; }
    ArchiveResult complete(const ArchiveCommand&, const ArchiveResult&) override { ++complete_calls; return complete_result; }
};

struct Executor final : ArchiveExecutor {
    ArchiveResult result{ArchiveResultCode::Archived, 1};
    int calls{0};
    ArchiveResult execute(const ArchiveCommand&) override { ++calls; return result; }
};

ArchiveCommand command() {
    return {"request-1", ArchiveOperation::Archive, "message", "item-1", "authority-1", "source-1", 1};
}
}

int main() {
    Authority authority;
    Store store;
    Executor executor;
    ArchiveTool tool(authority, store, executor);

    const auto ok = tool.handle(command());
    assert(ok.code == ArchiveResultCode::Archived);
    assert(executor.calls == 1);
    assert(store.begin_calls == 1);
    assert(store.complete_calls == 1);

    authority.allow = false;
    const auto denied = tool.handle(command());
    assert(denied.code == ArchiveResultCode::AuthorityRejected);
    assert(executor.calls == 1);

    authority.allow = true;
    store.begin_result = {ArchiveResultCode::AlreadyArchived, 4};
    const auto replay = tool.handle(command());
    assert(replay.code == ArchiveResultCode::AlreadyArchived);
    assert(executor.calls == 1);

    const ArchiveCommand invalid{"", ArchiveOperation::Archive, "message", "item-1", "authority-1", "source-1", 1};
    assert(tool.handle(invalid).code == ArchiveResultCode::InvalidRequest);

    return 0;
}
