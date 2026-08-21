#include <cassert>
#include <string>
#include "../../../src/tools/lifecycle/sort_by/sort_tool.h"

using namespace work_disk::tools::sort_by;

class Authority final : public SortAuthorityBoundary {
 public:
  bool allowed = true;
  mutable int calls = 0;
  bool authorised(const std::string&, const std::string&, const std::string&) const override {
    ++calls;
    return allowed;
  }
};

class Provider final : public SortProvider {
 public:
  int calls = 0;
  SortResult sort(const SortRequest& request) override {
    ++calls;
    return {SortCode::Success, {{request.target_type + ":1"}, {request.target_type + ":2"}}};
  }
};

int main() {
  Authority authority;
  Provider provider;
  SortTool tool(authority, provider);

  SortRequest request{"r1", "auth", "scope", "entry",
                      {{SortField::Number, SortDirection::Ascending}}, 0};
  auto result = tool.execute(request);
  assert(result.code == SortCode::Success);
  assert(provider.calls == 1);

  authority.allowed = false;
  result = tool.execute(request);
  assert(result.code == SortCode::AuthorityRejected);
  assert(provider.calls == 1);

  request.criteria.clear();
  result = tool.execute(request);
  assert(result.code == SortCode::InvalidRequest);
  assert(provider.calls == 1);
}
