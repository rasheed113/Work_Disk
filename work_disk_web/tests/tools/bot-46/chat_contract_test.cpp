#include "../../../src/tools/bot-46/chat/chat.h"
#include <cassert>
using namespace work_disk::tools::bot46;struct P:Provider{int calls{};Result apply(const Request&)override{++calls;return{true};}};int main(){P p;Request r{"r","a","u","c","msg",Operation::Send};assert(execute(r,p).accepted&&p.calls==1);r.conversation_reference.clear();assert(!execute(r,p).accepted&&p.calls==1);}
