#pragma once
#include "reaction_types.h"
namespace work_disk::tools::reaction {
class ReactionProvider { public: virtual ~ReactionProvider() = default; virtual bool apply(const ReactionRequest&, std::string& error) = 0; };
class ReactionTool { public: explicit ReactionTool(ReactionProvider& provider): provider_(provider) {} ReactionResult apply(const ReactionRequest& request) const; private: ReactionProvider& provider_; };
}
