#include "sort_tool.h"

namespace work_disk::tools::sort_by {

SortResult SortTool::execute(const SortRequest& request) const {
  if (request.request_id.empty() || request.authority_reference.empty() ||
      request.scope_reference.empty() || request.target_type.empty() ||
      request.criteria.empty()) {
    return {SortCode::InvalidRequest, {}};
  }

  if (!authority_.authorised(request.authority_reference,
                             request.scope_reference,
                             request.target_type)) {
    return {SortCode::AuthorityRejected, {}};
  }

  return provider_.sort(request);
}

}  // namespace work_disk::tools::sort_by
