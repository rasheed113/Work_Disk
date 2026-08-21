#pragma once
#include <string>
namespace work_disk::tools::bot25 {
struct Request { std::string request_id, authority_reference, moderator_reference, target_reference, policy_reference, action_reference; };
struct Result { bool accepted{false}; std::string decision_reference; };
class Provider { public: virtual ~Provider() = default; virtual Result moderate(const Request&) = 0; };
Result execute(const Request&, Provider&);
}