#include "../../../../../src/tools/trust/report/report_tool.h"
#include <cassert>
using namespace work_disk::tools::report;
struct P:ReportProvider{int calls=0;bool submit(const ReportRequest&,ReportResult& r)override{++calls;r.report_reference="report-1";return true;}};
int main(){P p;ReportTool t(p);ReportRequest bad;auto a=t.submit(bad);assert(!a.accepted&&p.calls==0);ReportRequest r{"req","auth","actor","target","spam","ctx"};auto b=t.submit(r);assert(b.accepted&&p.calls==1&&!b.report_reference.empty());}
