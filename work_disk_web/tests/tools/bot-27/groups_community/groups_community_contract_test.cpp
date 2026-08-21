#include "../../../src/tools/bot-27/groups_community/groups_community.h"
#include <cassert>
using namespace work_disk::tools::bot27;
struct P: Provider { int calls=0; Result apply(const Request& r) override { ++calls; return {true,r.community_reference}; } };
int main(){ P p; Request r{"r","auth","actor","c",Operation::Join}; assert(execute(r,p).accepted); assert(p.calls==1); r.authority_reference.clear(); assert(!execute(r,p).accepted); assert(p.calls==1); r.operation=static_cast<Operation>(99); assert(!execute(r,p)); }
