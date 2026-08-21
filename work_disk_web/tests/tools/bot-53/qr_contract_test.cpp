#include "../../../src/tools/bot-53/qr/qr.h"
#include <cassert>
using namespace work_disk::tools::bot53;
struct FakeProvider final : Provider { int enc{0}, dec{0}; Result encode(const EncodeRequest&) override { ++enc; return {true,"encoded-by-provider"}; } Result decode(const DecodeRequest&) override { ++dec; return {true,"decoded-by-provider"}; } };
int main(){ FakeProvider p; EncodeRequest e{"r1","c1","share","1","payload"}; assert(encode(e,p).accepted&&p.enc==1); DecodeRequest d{"r2","c1","encoded"}; assert(decode(d,p).accepted&&p.dec==1); EncodeRequest bad=e; bad.version.clear(); assert(!encode(bad,p).accepted&&p.enc==1); }
