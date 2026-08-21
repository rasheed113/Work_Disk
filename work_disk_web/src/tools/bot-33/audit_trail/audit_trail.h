#pragma once
#include <cstdint>
#include <string>

namespace work_disk::tools::bot33 {

enum class Operation { Append };

struct Event {
  std::string event_id;
  std::string request_id;
  std::string authority_reference;
  std::string actor_reference;
  std::string subject_reference;
  std::string event_type;
  std::string evidence_reference;
  std::int64_t occurred_at{0};
  std::int64_t sequence{0};
};

struct Result {
  bool accepted{false};
  std::string audit_reference;
};

class Provider {
 public:
  virtual ~Provider() = default;
  virtual Result append(const Event&) = 0;
};

Result execute(const Event&, Provider&);

} // namespace work_disk::tools::bot33
