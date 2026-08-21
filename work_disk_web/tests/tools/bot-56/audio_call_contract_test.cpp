#include "../../../src/tools/bot-56/audio_call/audio_call.h"
#include <cassert>
using namespace work_disk::tools::bot56; struct P:Provider{int n=0;Result apply(const Request&r)override{++n;return{true,r.session_reference};}}; int main(){P p;Request a{"1","c","",Operation::Invite};assert(execute(a,p).accepted&&p.n==1);Request b{"2","c","",Operation::Accept};assert(!execute(b,p).accepted&&p.n==1);}