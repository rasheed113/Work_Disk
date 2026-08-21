#include "../../../src/tools/bot-40/retry_recovery/retry_recovery.h"
#include <cassert>
using namespace work_disk::tools::bot40;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","op",0};assert(execute(r,p).accepted&&p.calls==1);r.attempt=-1;assert(!execute(r,p).accepted&&p.calls==1);}
