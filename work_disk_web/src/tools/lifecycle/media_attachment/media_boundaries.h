#pragma once
#include "media_types.h"
namespace work_disk::tools::media_attachment {
class MediaAuthority { public: virtual ~MediaAuthority() = default; virtual bool may_apply(const MediaCommand&) const = 0; };
class MediaProvider { public: virtual ~MediaProvider() = default; virtual MediaResult apply(const MediaCommand&) = 0; };
} // namespace work_disk::tools::media_attachment
