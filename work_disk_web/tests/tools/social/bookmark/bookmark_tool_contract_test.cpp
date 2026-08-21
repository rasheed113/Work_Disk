#include "../../../../../src/tools/social/bookmark/bookmark_tool.h"
#include <cassert>
using namespace work_disk::tools::bookmark; struct P:BookmarkProvider{int calls=0;bool save(const BookmarkRequest&,std::string&)override{++calls;return true;}}; int main(){P p;BookmarkTool t(p);BookmarkRequest b;auto x=t.save(b);assert(!x.accepted&&p.calls==0);BookmarkRequest r{"r","a","u","post","" ,1};auto y=t.save(r);assert(y.accepted&&p.calls==1);}
