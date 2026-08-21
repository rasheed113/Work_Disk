#include "../../../src/tools/bot-44/relationship/relationship.h"
#include <cassert>
using namespace work_disk::tools::bot44;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","s","rel",Operation::Create};assert(execute(r,p).accepted&&p.calls==1);r.subject_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
