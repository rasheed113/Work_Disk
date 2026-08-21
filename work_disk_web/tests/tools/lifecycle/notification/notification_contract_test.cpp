#include "../../../src/tools/lifecycle/notification/notification_types.h"
#include <cassert>
using namespace work_disk::tools::notification;
struct A:Authority{bool allow=true;int calls=0;bool may_deliver(const NotificationCommand&)const override{return allow;}};
struct P:Provider{int calls=0;NotificationResult deliver(const NotificationCommand&)const override{return {ResultCode::Accepted,"delivery"};}};
int main(){A a;P p;NotificationTool t(a,p);NotificationCommand c{"r","a","s","recipient","event","idem","v1",Channel::InApp,"payload"};assert(t.handle(c).code==ResultCode::Accepted);c.authority_reference.clear();assert(t.handle(c).code==ResultCode::InvalidRequest);return 0;}
