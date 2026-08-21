#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace work_disk::tools::search {

enum class SearchMode {
    Exact,
    Keyword,
    Prefix,
    Identifier,
    Filter,
};

enum class SearchOperator {
    Equals,
    Contains,
    StartsWith,
    GreaterThan,
    GreaterThanOrEqual,
    LessThan,
    LessThanOrEqual,
};

enum class SearchResultCode {
    Results,
    Empty,
    AuthorityRejected,
    InvalidRequest,
    InvalidScope,
    ExecutionFailed,
};

struct SearchCriterion {
    std::string field;
    SearchOperator operation{SearchOperator::Equals};
    std::string value;
};

struct SearchCommand {
    std::string request_id;
    std::string authority_reference;
    std::string scope_reference;
    std::string target_type;
    SearchMode mode{SearchMode::Keyword};
    std::string query;
    std::vector<SearchCriterion> criteria;
    std::uint32_t limit{20};
    std::string cursor;
};

struct SearchHit {
    std::string target_type;
    std::string target_id;
    double rank{0.0};
};

struct SearchResult {
    SearchResultCode code{SearchResultCode::InvalidRequest};
    std::vector<SearchHit> hits;
    std::string next_cursor;
};

} // namespace work_disk::tools::search
