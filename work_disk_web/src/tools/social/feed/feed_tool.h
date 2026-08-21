#pragma once
#include "feed_types.h"
namespace work_disk::tools::feed { class FeedProvider { public: virtual ~FeedProvider()=default; virtual bool assemble(const FeedRequest&,FeedResult&)=0; }; class FeedTool { FeedProvider& p_; public: explicit FeedTool(FeedProvider& p):p_(p){} FeedResult read(const FeedRequest&) const; }; }
