#include "../../../src/tools/bot-50/tool_registry/tool_registry.h"
#include <cassert>
using namespace work_disk::tools::bot50;struct P:Provider{int calls{};Result dispatch(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","tool","op"};assert(execute(r,p).accepted&&p.calls==1);r.tool_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
