#pragma once
#include <string>
#include <vector>
namespace work_disk::tools::notification {
enum class Channel { InApp, Push, Email, Sms };
enum class ResultCode { Accepted, InvalidRequest, AuthorityRejected };
struct NotificationCommand { std::string request_id; std::string authority_reference; std::string delivery_scope_reference; std::string recipient_reference; std::string event_reference; std::string idempotency_key; std::string expected_version; Channel channel; std::string payload_reference; };
struct NotificationResult { ResultCode code; std::string delivery_reference; };
class Authority { public: virtual ~Authority()=default; virtual bool may_deliver(const NotificationCommand&) const=0; };
class Provider { public: virtual ~Provider()=default; virtual NotificationResult deliver(const NotificationCommand&) const=0; };
class NotificationTool { public: NotificationTool(const Authority& a,const Provider& p):authority_(a),provider_(p){} NotificationResult handle(const NotificationCommand&) const; private: static bool valid(const NotificationCommand&); const Authority& authority_; const Provider& provider_; };
}
