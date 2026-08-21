#pragma once

#include "relationship_boundaries.h"

namespace work_disk::tools::social_relationship {

class RelationshipTool {
public:
    RelationshipTool(const RelationshipAuthority& authority, RelationshipProvider& provider)
        : authority_(authority), provider_(provider) {}

    static bool valid(const RelationshipCommand& command);
    RelationshipResult handle(const RelationshipCommand& command) const;

private:
    const RelationshipAuthority& authority_;
    RelationshipProvider& provider_;
};

} // namespace work_disk::tools::social_relationship
