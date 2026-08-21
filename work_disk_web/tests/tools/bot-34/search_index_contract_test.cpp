#include "../../../src/tools/bot-34/search_index/search_index.h"
#include <cassert>
using namespace work_disk::tools::bot34;
struct Provider final : work_disk::tools::bot34::Provider {
  int calls{0};
  Result search(const Query& q) override { ++calls; return {true,{q.text}}; }
};
int main() {
  Provider provider;
  Query valid{"request-1","authority-1","actor-1","scope-1","garment",MatchMode::Token};
  const auto result = execute(valid, provider);
  assert(result.accepted && provider.calls == 1 && result.result_references.size() == 1);
  Query missing_scope = valid;
  missing_scope.scope_reference.clear();
  assert(!execute(missing_scope, provider).accepted && provider.calls == 1);
  Query missing_text = valid;
  missing_text.text.clear();
  assert(!execute(missing_text, provider).accepted && provider.calls == 1);
}
