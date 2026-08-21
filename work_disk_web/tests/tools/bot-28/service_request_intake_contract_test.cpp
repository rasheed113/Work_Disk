#include "../../../src/tools/bot-28/service_request_intake/service_request_intake.h"
#include <cassert>
using namespace work_disk::tools::bot28;
struct FakeProvider final : Provider { int calls{0}; Result apply(const Request& r) override { ++calls; return {true,r.request_id}; } };
int main(){ FakeProvider p; Request r{"r1","auth","actor","service",Operation::Submit,"payload"}; auto ok=execute(r,p); assert(ok.accepted&&p.calls==1); Request bad=r; bad.authority_reference.clear(); assert(!execute(bad,p).accepted&&p.calls==1); Request no_payload=r; no_payload.payload_reference.clear(); assert(!execute(no_payload,p).accepted&&p.calls==1); }
