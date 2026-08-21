#include "../../../src/tools/bot-58/call_signalling/call_signalling.h"
#include <cassert>
using namespace work_disk::tools::bot58; struct P:Provider{int n=0;Result signal(const Request&){++n;return{true};}}; int main(){P p;Request r{"1","c","s","offer"};assert(execute(r,p).accepted);r.signal.clear();assert(!execute(r,p).accepted&&p.n==1);}