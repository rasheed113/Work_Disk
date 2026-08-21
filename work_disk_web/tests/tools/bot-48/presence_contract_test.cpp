#include "../../../src/tools/bot-48/presence/presence.h"
#include <cassert>
using namespace work_disk::tools::bot48;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","s","online",Operation::Publish};assert(execute(r,p).accepted&&p.calls==1);r.status_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
