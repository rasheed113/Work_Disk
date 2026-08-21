#include "messaging_types.h"
namespace work_disk::tools::messaging {
bool MessagingTool::valid(const MessageCommand&c){return !c.request_id.empty()&&!c.authority_reference.empty()&&!c.conversation_scope_reference.empty()&&!c.actor_reference.empty()&&!c.target_reference.empty()&&!c.content_reference.empty()&&!c.idempotency_key.empty()&&!c.expected_version.empty();}
MessageResult MessagingTool::handle(const MessageCommand&c)const{if(!valid(c))return{ResultCode::InvalidRequest,{}};if(!authority_.may_message(c))return{ResultCode::AuthorityRejected,{}};return provider_.apply(c);}
}
