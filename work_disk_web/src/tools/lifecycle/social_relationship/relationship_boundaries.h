#pragma once

#include "relationship_types.h"

namespace work_disk::tools::social_relationship {

class RelationshipAuthority {
public:
    virtual ~RelationshipAuthority() = default;
    virtual bool may_apply(const RelationshipCommand& command) const = 0;
};

class RelationshipProvider {
public:
    virtual ~RelationshipProvider() = default;
    virtual RelationshipResult apply(const RelationshipCommand& command) = 0;
};

} // namespace work_disk::tools::social_relationship
