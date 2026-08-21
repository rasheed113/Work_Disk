#include "search_tool.h"

#include <cassert>
#include <string>

using namespace work_disk::tools::search;

namespace {

struct FakeAuthority final : SearchAuthority {
    bool allow{true};
    SearchCommand last_command{};

    bool authorised(const SearchCommand& command) const override {
        const_cast<FakeAuthority*>(this)->last_command = command;
        return allow;
    }
};

struct FakeProvider final : SearchProvider {
    SearchResult result{SearchResultCode::Empty, {}, {}};
    SearchCommand last_command{};
    int calls{0};

    SearchResult execute(const SearchCommand& command) override {
        last_command = command;
        ++calls;
        return result;
    }
};

SearchCommand valid_command() {
    SearchCommand command;
    command.request_id = "req-08";
    command.authority_reference = "authority-08";
    command.scope_reference = "account-scope-01";
    command.target_type = "entry";
    command.mode = SearchMode::Keyword;
    command.query = "needle";
    command.limit = 20;
    return command;
}

} // namespace

int main() {
    FakeAuthority authority;
    FakeProvider provider;
    SearchTool tool(authority, provider);

    assert(!SearchTool::valid(SearchCommand{}));

    auto command = valid_command();
    assert(SearchTool::valid(command));

    authority.allow = false;
    auto rejected = tool.handle(command);
    assert(rejected.code == SearchResultCode::AuthorityRejected);
    assert(provider.calls == 0);

    authority.allow = true;
    provider.result = {
        SearchResultCode::Results,
        {{"entry", "entry-123", 1.0}},
        "cursor-2"
    };
    auto results = tool.handle(command);
    assert(results.code == SearchResultCode::Results);
    assert(results.hits.size() == 1);
    assert(results.hits.front().target_id == "entry-123");
    assert(results.next_cursor == "cursor-2");
    assert(provider.calls == 1);
    assert(provider.last_command.scope_reference == "account-scope-01");

    command.query.clear();
    command.criteria.push_back({"status", SearchOperator::Equals, "open"});
    provider.result = {SearchResultCode::Empty, {}, {}};
    auto empty = tool.handle(command);
    assert(empty.code == SearchResultCode::Empty);
    assert(provider.calls == 2);

    command.criteria.clear();
    auto invalid = tool.handle(command);
    assert(invalid.code == SearchResultCode::InvalidRequest);
    assert(provider.calls == 2);

    return 0;
}
