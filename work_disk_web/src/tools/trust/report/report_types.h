#pragma once
#include <string>
namespace work_disk::tools::report {
struct ReportRequest { std::string request_id; std::string authority_reference; std::string reporter_reference; std::string target_reference; std::string reason_code; std::string context_reference; };
struct ReportResult { bool accepted{false}; std::string error; std::string report_reference; };
}
