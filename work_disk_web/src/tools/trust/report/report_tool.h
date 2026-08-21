#pragma once
#include "report_types.h"
namespace work_disk::tools::report {
class ReportProvider { public: virtual ~ReportProvider()=default; virtual bool submit(const ReportRequest&, ReportResult&)=0; };
class ReportTool { ReportProvider& provider_; public: explicit ReportTool(ReportProvider& p):provider_(p){} ReportResult submit(const ReportRequest&) const; };
}
