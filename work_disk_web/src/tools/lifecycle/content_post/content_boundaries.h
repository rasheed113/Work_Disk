#pragma once

#include "content_types.h"

namespace work_disk::tools::content_post {

class ContentAuthority {
public:
    virtual ~ContentAuthority() = default;
    virtual bool may_create(const ContentCommand& command) const = 0;
};

class ContentProvider {
public:
    virtual ~ContentProvider() = default;
    virtual ContentResult create(const ContentCommand& command) = 0;
};

} // namespace work_disk::tools::content_post
