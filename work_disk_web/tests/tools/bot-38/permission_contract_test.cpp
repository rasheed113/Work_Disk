#include "../../../src/tools/bot-38/permission/permission.h"
#include <cassert>
using namespace work_disk::tools::bot38; struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}}; int main(){P p;Request r{"r","a","u","s","c",Operation::Grant};assert(execute(r,p).accepted&&p.calls==1);r.subject_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
