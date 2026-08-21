#include "../../../../../src/tools/social/share/share_tool.h"
#include <cassert>
using namespace work_disk::tools::share; struct P:ShareProvider{int calls=0;bool share(const ShareRequest&,std::string&)override{++calls;return true;}}; int main(){P p;ShareTool t(p);ShareRequest b;auto x=t.share(b);assert(!x.accepted&&p.calls==0);ShareRequest r{"r","a","u","post","feed","repost",1};auto y=t.share(r);assert(y.accepted&&p.calls==1);}
