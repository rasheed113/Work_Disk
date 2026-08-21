#include "../../../src/tools/bot-57/video_call/video_call.h"
#include <cassert>
using namespace work_disk::tools::bot57; struct P:Provider{int n=0;Result apply(const Request&r)override{++n;return{true,r.session_reference};}}; int main(){P p;Request a{"1","c","",Operation::Invite};assert(execute(a,p).accepted);Request b{"2","c","",Operation::End};assert(!execute(b,p).accepted);}