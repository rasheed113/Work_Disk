#include <cassert>
#include <string>

#include "../../../../src/tools/lifecycle/filter/filter_tool.h"

namespace {
using namespace work_disk::tools::filter;

class TestAuthority final : public FilterAuthority {
public:
    bool allowed{true};
    int calls{0};

    bool authorised(const std::string&, const std::string&) const override {
        ++const_cast<TestAuthority*>(this)->calls;
        return allowed;
    }
};

class TestProvider final : public FilterProvider {
public:
    mutable int calls{0};

    FilterResult filter(const FilterCommand& command) const override {
        ++calls;
        FilterResult result;
        result.code = FilterResultCode::Results;
        result.hits.push_back({command.target_type, "T-1"});
        result.next_cursor = "next";
        return result;
    }
};

FilterCommand valid_command() {
    FilterCommand command;
    command.request_id = "req-10";
    command.authority_reference = "auth-10";
    command.scope_reference = "scope-10";
    command.target_type = "entry";
    command.criteria.push_back({"status", FilterOperator::Equals, "active"});
    return command;
}

void test_invalid_request_does_not_call_authority_or_provider() {
    TestAuthority authority;
    TestProvider provider;
    FilterTool tool(authority, provider);
    FilterCommand command = valid_command();
    command.criteria.clear();

    const auto result = tool.execute(command);
    assert(result.code == FilterResultCode::InvalidRequest);
    assert(authority.calls == 0);
    assert(provider.calls == 0);
}

void test_authority_rejection_blocks_provider() {
    TestAuthority authority;
    authority.allowed = false;
    TestProvider provider;
    FilterTool tool(authority, provider);

    const auto result = tool.execute(valid_command());
    assert(result.code == FilterResultCode::AuthorityRejected);
    assert(authority.calls == 1);
    assert(provider.calls == 0);
}

void test_valid_filter_reaches_provider() {
    TestAuthority authority;
    TestProvider provider;
    FilterTool tool(authority, provider);

    const auto result = tool.execute(valid_command());
    assert(result.code == FilterResultCode::Results);
    assert(result.hits.size() == 1);
    assert(result.hits.front().target_id == "T-1");
    assert(result.next_cursor == "next");
    assert(authority.calls == 1);
    assert(provider.calls == 1);
}

void test_empty_field_is_invalid() {
    TestAuthority authority;
    TestProvider provider;
    FilterTool tool(authority, provider);
    FilterCommand command = valid_command();
    command.criteria.front().field.clear();

    const auto result = tool.execute(command);
    assert(result.code == FilterResultCode::InvalidRequest);
    assert(provider.calls == 0);
}

} // namespace

int main() {
    test_invalid_request_does_not_call_authority_or_provider();
    test_authority_rejection_blocks_provider();
    test_valid_filter_reaches_provider();
    test_empty_field_is_invalid();
    return 0;
}
