#include "reaction_tool.h"
namespace work_disk::tools::reaction {
ReactionResult ReactionTool::apply(const ReactionRequest& r) const {
 if (r.request_id.empty() || r.authority_reference.empty() || r.actor_reference.empty() || r.target_reference.empty() || r.reaction_type.empty()) return {false,"InvalidRequest"};
 std::string error; if (!provider_.apply(r,error)) return {false,error.empty()?"Rejected":error}; return {true,{}};
}
}
