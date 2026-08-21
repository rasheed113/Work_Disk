#include "../../../src/tools/lifecycle/mark_unmark/mark_tool.h"

#include <cassert>

using namespace work_disk::tools::mark;

namespace {
struct FakeAuthority final : MarkAuthority {
    bool allow{true};
    int calls{0};
    bool authorised(const std::string&, const std::string&) const override {
        ++const_cast<FakeAuthority*>(this)->calls;
        return allow;
    }
};

struct FakeStore final : MarkSelectionStore {
    SelectionSnapshot state{};
    int mark_calls{0};
    int unmark_calls{0};
    int mark_all_calls{0};
    int clear_calls{0};
    bool succeed{true};

    bool mark(const MarkCommand& command) override {
        ++mark_calls;
        state.scope_reference = command.scope_reference;
        state.mode = SelectionMode::Individual;
        state.targets.push_back(command.target);
        return succeed;
    }
    bool unmark(const UnmarkCommand& command) override {
        ++unmark_calls;
        for (auto it = state.targets.begin(); it != state.targets.end(); ++it) {
            if (it->target_type == command.target.target_type && it->target_id == command.target.target_id) {
                state.targets.erase(it);
                break;
            }
        }
        return succeed;
    }
    bool mark_all(const MarkAllCommand& command) override {
        ++mark_all_calls;
        state.scope_reference = command.scope_reference;
        state.mode = SelectionMode::AllInScope;
        return succeed;
    }
    bool clear(const ClearCommand& command) override {
        ++clear_calls;
        state.scope_reference = command.scope_reference;
        state.mode = SelectionMode::Individual;
        state.targets.clear();
        return succeed;
    }
    SelectionSnapshot snapshot(const std::string&) const override { return state; }
};

MarkCommand mark_command() {
    return {"r1", "auth", "scope", {"entry", "1"}};
}
}

int main() {
    FakeAuthority authority;
    FakeStore store;
    MarkTool tool(authority, store);

    auto marked = tool.mark(mark_command());
    assert(marked.code == MarkResultCode::Marked);
    assert(store.mark_calls == 1);
    assert(marked.selection.targets.size() == 1);

    auto unmarked = tool.unmark({"r2", "auth", "scope", {"entry", "1"}});
    assert(unmarked.code == MarkResultCode::Unmarked);
    assert(store.unmark_calls == 1);
    assert(unmarked.selection.targets.empty());

    auto all = tool.mark_all({"r3", "auth", "scope"});
    assert(all.code == MarkResultCode::MarkAllApplied);
    assert(all.selection.mode == SelectionMode::AllInScope);
    assert(store.mark_all_calls == 1);

    auto cleared = tool.clear({"r4", "auth", "scope"});
    assert(cleared.code == MarkResultCode::Cleared);
    assert(store.clear_calls == 1);

    authority.allow = false;
    auto denied = tool.mark(mark_command());
    assert(denied.code == MarkResultCode::AuthorityRejected);
    assert(store.mark_calls == 1);

    auto invalid = tool.mark({"", "auth", "scope", {"entry", "1"}});
    assert(invalid.code == MarkResultCode::InvalidRequest);
    assert(store.mark_calls == 1);

    return 0;
}
