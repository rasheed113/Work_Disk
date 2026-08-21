#include "../../../src/tools/action_board/action_board.h"

#include <cassert>

using namespace work_disk::tools::action_board;

class TestAuthority final : public ActionAuthority {
public:
    bool allowed{true};
    int calls{0};

    bool allows(const std::string&, const ActionContext&, const SelectedSet&) const override {
        ++const_cast<TestAuthority*>(this)->calls;
        return allowed;
    }
};

class TestProvider final : public ActionProvider {
public:
    int calls{0};

    ActionResultCode discover(const ActionBoardCommand&, std::vector<ActionDescriptor>& actions) const override {
        ++const_cast<TestProvider*>(this)->calls;
        actions.push_back({"delete", "Delete", "BOT-04"});
        actions.push_back({"move", "Move", "MOVE"});
        return ActionResultCode::ActionsAvailable;
    }
};

static ActionBoardCommand valid_command() {
    return {"req-1", "auth-1", {"diary", "scope-1"}, {"selection-1", 2, false}};
}

int main() {
    TestAuthority authority;
    TestProvider provider;
    ActionBoard board(authority, provider);

    auto result = board.discover(valid_command());
    assert(result.code == ActionResultCode::ActionsAvailable);
    assert(result.actions.size() == 2);
    assert(provider.calls == 1);

    authority.allowed = false;
    result = board.discover(valid_command());
    assert(result.code == ActionResultCode::AuthorityRejected);
    assert(provider.calls == 1);

    authority.allowed = true;
    auto invalid = valid_command();
    invalid.selection.selected_count = 0;
    invalid.selection.all_in_scope = false;
    result = board.discover(invalid);
    assert(result.code == ActionResultCode::InvalidRequest);
    assert(provider.calls == 1);

    auto mark_all = valid_command();
    mark_all.selection.selected_count = 0;
    mark_all.selection.all_in_scope = true;
    result = board.discover(mark_all);
    assert(result.code == ActionResultCode::ActionsAvailable);
    assert(provider.calls == 2);
}
