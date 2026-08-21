#pragma once

#include "search_boundaries.h"

namespace work_disk::tools::search {

class SearchTool {
public:
    SearchTool(const SearchAuthority& authority, SearchProvider& provider)
        : authority_(authority), provider_(provider) {}

    static bool valid(const SearchCommand& command);
    SearchResult handle(const SearchCommand& command) const;

private:
    const SearchAuthority& authority_;
    SearchProvider& provider_;
};

} // namespace work_disk::tools::search
