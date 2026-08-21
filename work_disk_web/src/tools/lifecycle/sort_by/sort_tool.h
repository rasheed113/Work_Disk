#pragma once

#include "sort_boundaries.h"

namespace work_disk::tools::sort_by {

class SortTool {
 public:
  SortTool(const SortAuthorityBoundary& authority, SortProvider& provider)
      : authority_(authority), provider_(provider) {}

  SortResult execute(const SortRequest& request) const;

 private:
  const SortAuthorityBoundary& authority_;
  SortProvider& provider_;
};

}  // namespace work_disk::tools::sort_by
