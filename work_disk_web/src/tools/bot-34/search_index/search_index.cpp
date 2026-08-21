#include "search_index.h"

namespace work_disk::tools::bot34 {

Result execute(const Query& query, Provider& provider) {
  if (query.request_id.empty() || query.authority_reference.empty() ||
      query.actor_reference.empty() || query.scope_reference.empty() ||
      query.text.empty()) {
    return {};
  }
  return provider.search(query);
}

} // namespace work_disk::tools::bot34
