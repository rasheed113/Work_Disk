#pragma once
#include <string>
namespace work_disk::tools::messaging {
enum class Operation { Send, Reply };
enum class ResultCode { Accepted, InvalidRequest, AuthorityRejected };
struct MessageCommand { std::string request_id; std::string authority_reference; std::string conversation_scope_reference; std::string actor_reference; std::string target_reference; std::string content_reference; std::string idempotency_key; std::string expected_version; Operation operation; };
struct MessageResult { ResultCode code; std::string message_reference; };
class Authority { public: virtual ~Authority()=default; virtual bool may_message(const MessageCommand&) const=0; };
class Provider { public: virtual ~Provider()=default; virtual MessageResult apply(const MessageCommand&) const=0; };
class MessagingTool { public: MessagingTool(const Authority&a,const Provider&p):authority_(a),provider_(p){} MessageResult handle(const MessageCommand&) const; private: static bool valid(const MessageCommand&); const Authority& authority_; const Provider& provider_; };
}
