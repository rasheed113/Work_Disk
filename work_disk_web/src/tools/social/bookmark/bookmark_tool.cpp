#include "bookmark_tool.h"
namespace work_disk::tools::bookmark { BookmarkResult BookmarkTool::save(const BookmarkRequest& r) const { if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.target_reference.empty()) return {false,"InvalidRequest"}; std::string e; if(!p_.save(r,e)) return {false,e.empty()?"Rejected":e}; return {true,{}}; } }
