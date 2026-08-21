#include "../../../src/tools/bot-45/feed/feed.h"
#include <cassert>
using namespace work_disk::tools::bot45;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","scope","cursor"};assert(execute(r,p).accepted&&p.calls==1);r.scope_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
