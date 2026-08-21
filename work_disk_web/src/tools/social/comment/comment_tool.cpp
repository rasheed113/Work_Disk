#include "comment_tool.h"
namespace work_disk::tools::comment { CommentResult CommentTool::submit(const CommentRequest& r) const { if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.target_reference.empty()||r.body.empty()) return {false,"InvalidRequest"}; std::string e; if(!p_.submit(r,e)) return {false,e.empty()?"Rejected":e}; return {true,{}}; } }
