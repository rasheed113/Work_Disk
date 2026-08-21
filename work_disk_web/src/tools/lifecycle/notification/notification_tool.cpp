#include "notification_types.h"
namespace work_disk::tools::notification {
bool NotificationTool::valid(const NotificationCommand& c){ return !c.request_id.empty()&&!c.authority_reference.empty()&&!c.delivery_scope_reference.empty()&&!c.recipient_reference.empty()&&!c.event_reference.empty()&&!c.idempotency_key.empty()&&!c.expected_version.empty()&&!c.payload_reference.empty(); }
NotificationResult NotificationTool::handle(const NotificationCommand& c) const { if(!valid(c)) return {ResultCode::InvalidRequest,{}}; if(!authority_.may_deliver(c)) return {ResultCode::AuthorityRejected,{}}; return provider_.deliver(c); }
}
