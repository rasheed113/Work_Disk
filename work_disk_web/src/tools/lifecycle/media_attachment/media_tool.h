#pragma once
#include "media_boundaries.h"
namespace work_disk::tools::media_attachment {
class MediaTool {
public:
    MediaTool(const MediaAuthority& authority, MediaProvider& provider) : authority_(authority), provider_(provider) {}
    static bool valid(const MediaCommand& command);
    MediaResult handle(const MediaCommand& command) const;
private:
    const MediaAuthority& authority_;
    MediaProvider& provider_;
};
} // namespace work_disk::tools::media_attachment
