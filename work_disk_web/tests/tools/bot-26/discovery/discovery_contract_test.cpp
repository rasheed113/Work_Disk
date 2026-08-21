#include "../../../src/tools/bot-26/discovery/discovery.h"
#include <cassert>
using namespace work_disk::tools::bot26;
struct P: Provider { int calls=0; Result discover(const Request& r) override { ++calls; return {true,{r.query}}; } };
int main(){ P p; Request r{"r","auth","actor","garment",20}; assert(execute(r,p).accepted); assert(p.calls==1); r.authority_reference.clear(); assert(!execute(r,p).accepted); assert(p.calls==1); r.limit=101; assert(!execute(r,p).accepted); }
