#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace work_disk::tools::sort_by {

enum class SortField { Number, Size, Name };
enum class SortDirection { Ascending, Descending };

enum class SortCode {
  Success,
  InvalidRequest,
  AuthorityRejected,
  ProviderFailure,
};

struct SortCriterion {
  SortField field;
  SortDirection direction;
};

struct SortTargetRef {
  std::string opaque_id;
};

struct SortRequest {
  std::string request_id;
  std::string authority_reference;
  std::string scope_reference;
  std::string target_type;
  std::vector<SortCriterion> criteria;
  std::size_t limit{0};
};

struct SortResult {
  SortCode code{SortCode::InvalidRequest};
  std::vector<SortTargetRef> targets;
};

}  // namespace work_disk::tools::sort_by
