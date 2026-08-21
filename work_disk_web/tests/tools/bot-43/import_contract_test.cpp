#include "../../../src/tools/bot-43/import/import.h"
#include <cassert>
using namespace work_disk::tools::bot43;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","s","payload"};assert(execute(r,p).accepted&&p.calls==1);r.payload_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
