#include "../../../src/tools/bot-49/ai_assistant/ai_assistant.h"
#include <cassert>
using namespace work_disk::tools::bot49;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","ctx","prompt"};assert(execute(r,p).accepted&&p.calls==1);r.context_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
