#include "../../../src/tools/bot-39/sync/sync.h"
#include <cassert>
using namespace work_disk::tools::bot39;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","s","c"};assert(execute(r,p).accepted&&p.calls==1);r.cursor_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
