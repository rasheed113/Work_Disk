#include "../../../src/tools/bot-47/file_transfer/file_transfer.h"
#include <cassert>
using namespace work_disk::tools::bot47;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","f","s",Operation::Upload};assert(execute(r,p).accepted&&p.calls==1);r.file_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
