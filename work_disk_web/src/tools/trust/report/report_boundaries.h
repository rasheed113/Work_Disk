#pragma once
namespace work_disk::tools::report {
struct ReportBoundary {
 static constexpr bool mutates_target = false;
 static constexpr bool grants_authority = false;
 static constexpr bool executes_enforcement = false;
};
}
