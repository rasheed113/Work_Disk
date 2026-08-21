#include "filter_tool.h"

namespace work_disk::tools::filter {

FilterTool::FilterTool(const FilterAuthority& authority,
                       const FilterProvider& provider)
    : authority_(authority), provider_(provider) {}

FilterResult FilterTool::execute(const FilterCommand& command) const {
    FilterResult invalid{};
    invalid.code = FilterResultCode::InvalidRequest;

    if (command.request_id.empty() || command.authority_reference.empty() ||
        command.scope_reference.empty() || command.target_type.empty() ||
        command.criteria.empty() || command.limit == 0) {
        return invalid;
    }

    for (const auto& criterion : command.criteria) {
        if (criterion.field.empty()) {
            return invalid;
        }
    }

    if (!authority_.authorised(command.authority_reference,
                               command.scope_reference)) {
        FilterResult rejected{};
        rejected.code = FilterResultCode::AuthorityRejected;
        return rejected;
    }

    return provider_.filter(command);
}

} // namespace work_disk::tools::filter
