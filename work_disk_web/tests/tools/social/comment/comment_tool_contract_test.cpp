#include "../../../../../src/tools/social/comment/comment_tool.h"
#include <cassert>
using namespace work_disk::tools::comment; struct P:CommentProvider{int calls=0;bool submit(const CommentRequest&,std::string&)override{++calls;return true;}}; int main(){P p;CommentTool t(p);CommentRequest b;auto x=t.submit(b);assert(!x.accepted&&p.calls==0);CommentRequest r{"r","a","u","post","hello",1};auto y=t.submit(r);assert(y.accepted&&p.calls==1);}
