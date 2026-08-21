#include "../../../src/tools/bot-42/export/export.h"
#include <cassert>
using namespace work_disk::tools::bot42;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","s","json"};assert(execute(r,p).accepted&&p.calls==1);r.scope_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
