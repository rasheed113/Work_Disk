#pragma once

#include "filter_boundaries.h"

namespace work_disk::tools::filter {

class FilterTool {
public:
    FilterTool(const FilterAuthority& authority, const FilterProvider& provider);

    FilterResult execute(const FilterCommand& command) const;

private:
    const FilterAuthority& authority_;
    const FilterProvider& provider_;
};

} // namespace work_disk::tools::filter
