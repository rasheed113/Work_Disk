#pragma once

#include "sort_types.h"

namespace work_disk::tools::sort_by {

class SortAuthorityBoundary {
 public:
  virtual ~SortAuthorityBoundary() = default;
  virtual bool authorised(const std::string& authority_reference,
                          const std::string& scope_reference,
                          const std::string& target_type) const = 0;
};

class SortProvider {
 public:
  virtual ~SortProvider() = default;
  virtual SortResult sort(const SortRequest& request) = 0;
};

}  // namespace work_disk::tools::sort_by
