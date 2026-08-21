#pragma once
#include "share_types.h"
namespace work_disk::tools::share { class ShareProvider { public: virtual ~ShareProvider()=default; virtual bool share(const ShareRequest&,std::string&)=0; }; class ShareTool { ShareProvider& p_; public: explicit ShareTool(ShareProvider& p):p_(p){} ShareResult share(const ShareRequest&) const; }; }
