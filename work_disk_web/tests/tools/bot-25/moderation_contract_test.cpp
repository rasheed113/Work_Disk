#include "../../../src/tools/bot-25/moderation.h"
#include <cassert>
using namespace work_disk::tools::bot25;
struct P:Provider{int calls=0; Result moderate(const Request&) override{++calls;return{true,"d1"};}};
int main(){P p; Request r{"r","a","m","t","policy","action"}; auto x=execute(r,p); assert(x.accepted&&p.calls==1); Request bad=r;bad.policy_reference.clear();auto y=execute(bad,p);assert(!y.accepted&&p.calls==1);}