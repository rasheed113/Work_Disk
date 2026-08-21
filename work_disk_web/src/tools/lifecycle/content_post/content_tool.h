#pragma once

#include "content_boundaries.h"

namespace work_disk::tools::content_post {

class ContentTool {
public:
    ContentTool(const ContentAuthority& authority, ContentProvider& provider)
        : authority_(authority), provider_(provider) {}

    static bool valid(const ContentCommand& command);
    ContentResult handle(const ContentCommand& command) const;

private:
    const ContentAuthority& authority_;
    ContentProvider& provider_;
};

} // namespace work_disk::tools::content_post
