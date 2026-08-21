#pragma once

#include "search_types.h"

namespace work_disk::tools::search {

class SearchAuthority {
public:
    virtual ~SearchAuthority() = default;
    virtual bool authorised(const SearchCommand& command) const = 0;
};

class SearchProvider {
public:
    virtual ~SearchProvider() = default;
    virtual SearchResult execute(const SearchCommand& command) = 0;
};

} // namespace work_disk::tools::search
