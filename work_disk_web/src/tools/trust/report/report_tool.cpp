#include "report_tool.h"
namespace work_disk::tools::report {
ReportResult ReportTool::submit(const ReportRequest& r) const {
 ReportResult out;
 if(r.request_id.empty() || r.authority_reference.empty() || r.reporter_reference.empty() || r.target_reference.empty() || r.reason_code.empty()) { out.error="InvalidRequest"; return out; }
 if(!provider_.submit(r,out)) { out.accepted=false; if(out.error.empty()) out.error="Rejected"; return out; }
 out.accepted=true; return out;
}
}
