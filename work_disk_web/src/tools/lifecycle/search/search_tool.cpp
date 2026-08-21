#include "search_tool.h"

namespace work_disk::tools::search {

bool SearchTool::valid(const SearchCommand& command) {
    const bool has_query = !command.query.empty();
    const bool has_criteria = !command.criteria.empty();
    return !command.request_id.empty()
        && !command.authority_reference.empty()
        && !command.scope_reference.empty()
        && !command.target_type.empty()
        && (has_query || has_criteria)
        && command.limit > 0;
}

SearchResult SearchTool::handle(const SearchCommand& command) const {
    if (!valid(command)) {
        return {SearchResultCode::InvalidRequest, {}, {}};
    }

    if (!authority_.authorised(command)) {
        return {SearchResultCode::AuthorityRejected, {}, {}};
    }

    const auto result = provider_.execute(command);
    switch (result.code) {
        case SearchResultCode::Results:
        case SearchResultCode::Empty:
        case SearchResultCode::ExecutionFailed:
            return result;
        case SearchResultCode::AuthorityRejected:
        case SearchResultCode::InvalidRequest:
        case SearchResultCode::InvalidScope:
            return result;
    }

    return {SearchResultCode::ExecutionFailed, {}, {}};
}

} // namespace work_disk::tools::search
