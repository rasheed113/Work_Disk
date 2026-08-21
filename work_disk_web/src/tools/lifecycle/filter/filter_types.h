#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace work_disk::tools::filter {

enum class FilterOperator {
    Equals,
    NotEquals,
    Contains,
    StartsWith,
    GreaterThan,
    GreaterThanOrEqual,
    LessThan,
    LessThanOrEqual,
};

enum class FilterMatch {
    All,
    Any,
};

enum class FilterResultCode {
    Results,
    Empty,
    AuthorityRejected,
    InvalidRequest,
    InvalidScope,
    ExecutionFailed,
};

struct FilterCriterion {
    std::string field;
    FilterOperator operation{FilterOperator::Equals};
    std::string value;
};

struct FilterCommand {
    std::string request_id;
    std::string authority_reference;
    std::string scope_reference;
    std::string target_type;
    FilterMatch match{FilterMatch::All};
    std::vector<FilterCriterion> criteria;
    std::uint32_t limit{20};
    std::string cursor;
};

struct FilterHit {
    std::string target_type;
    std::string target_id;
};

struct FilterResult {
    FilterResultCode code{FilterResultCode::InvalidRequest};
    std::vector<FilterHit> hits;
    std::string next_cursor;
};

} // namespace work_disk::tools::filter
