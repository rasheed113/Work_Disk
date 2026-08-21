#include "../../../src/tools/bot-55/voice_message/voice_message.h"
#include <cassert>
using namespace work_disk::tools::bot55;
struct P:Provider{int n=0;Result send(const Request&r)override{++n;return{true,r.media_reference};}};
int main(){P p; Request r{"r","c","m"}; assert(execute(r,p).accepted&&p.n==1); r.media_reference.clear(); assert(!execute(r,p).accepted&&p.n==1);}