#pragma once
#include <string>

namespace work_disk::tools::bot28 {

enum class Operation { Submit, Withdraw };

struct Request {
  std::string request_id;
  std::string authority_reference;
  std::string actor_reference;
  std::string service_reference;
  Operation operation;
  std::string payload_reference;
};

struct Result {
  bool accepted{false};
  std::string case_reference;
};

class Provider {
 public:
  virtual ~Provider() = default;
  virtual Result apply(const Request&) = 0;
};

Result execute(const Request&, Provider&);

} // namespace work_disk::tools::bot28
