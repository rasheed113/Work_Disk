#pragma once

#include "filter_types.h"

namespace work_disk::tools::filter {

class FilterAuthority {
public:
    virtual ~FilterAuthority() = default;
    virtual bool authorised(const std::string& authority_reference,
                            const std::string& scope_reference) const = 0;
};

class FilterProvider {
public:
    virtual ~FilterProvider() = default;
    virtual FilterResult filter(const FilterCommand& command) const = 0;
};

} // namespace work_disk::tools::filter
