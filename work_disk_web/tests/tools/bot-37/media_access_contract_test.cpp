#include "../../../src/tools/bot-37/media_access/media_access.h"
#include <cassert>
using namespace work_disk::tools::bot37;
struct P:Provider{int calls{};Result apply(const Request&r)override{++calls;return{true,r.media_reference};}};
int main(){P p;Request r{"r","a","u","m",Operation::Acquire};assert(execute(r,p).accepted&&p.calls==1);r.media_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
