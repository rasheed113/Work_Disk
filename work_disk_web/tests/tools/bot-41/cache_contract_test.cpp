#include "../../../src/tools/bot-41/cache/cache.h"
#include <cassert>
using namespace work_disk::tools::bot41;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","k",Operation::Read};assert(execute(r,p).accepted&&p.calls==1);r.key_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
