#include "../../../../src/tools/lifecycle/messaging/messaging_types.h"
#include <cassert>
using namespace work_disk::tools::messaging;
struct A:Authority{bool allow=true;bool may_message(const MessageCommand&)const override{return allow;}};struct P:Provider{MessageResult apply(const MessageCommand&)const override{return{ResultCode::Accepted,"m"};}};
int main(){A a;P p;MessagingTool t(a,p);MessageCommand c{"r","a","s","actor","target","content","idem","v1",Operation::Send};assert(t.handle(c).code==ResultCode::Accepted);c.authority_reference.clear();assert(t.handle(c).code==ResultCode::InvalidRequest);return 0;}
