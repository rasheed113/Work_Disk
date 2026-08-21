#include "../../../../../src/tools/social/feed/feed_tool.h"
#include <cassert>
using namespace work_disk::tools::feed; struct P:FeedProvider{int calls=0;bool assemble(const FeedRequest&,FeedResult& r)override{++calls;r.items.push_back({"post",1});return true;}}; int main(){P p;FeedTool t(p);FeedRequest b;auto x=t.read(b);assert(!x.accepted&&p.calls==0);FeedRequest r{"r","a","u","home","",20};auto y=t.read(r);assert(y.accepted&&p.calls==1&&y.items.size()==1);FeedRequest bad{"r","a","u","home","",201};auto z=t.read(bad);assert(!z.accepted&&p.calls==1);}
