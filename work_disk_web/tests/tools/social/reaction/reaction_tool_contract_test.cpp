#include "../../../../../src/tools/social/reaction/reaction_tool.h"
#include <cassert>
using namespace work_disk::tools::reaction;
struct P: ReactionProvider { int calls=0; bool apply(const ReactionRequest&,std::string&) override {++calls; return true;} };
int main(){ P p; ReactionTool t(p); ReactionRequest bad; auto a=t.apply(bad); assert(!a.accepted && p.calls==0); ReactionRequest r{"r1","auth","actor","target","like",1}; auto b=t.apply(r); assert(b.accepted && p.calls==1); }
