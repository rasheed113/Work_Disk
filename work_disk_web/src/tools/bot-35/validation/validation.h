#pragma once
#include <string>

namespace work_disk::tools::bot35 {

enum class Operation { Validate, Revalidate };

struct Request {
  std::string request_id;
  std::string authority_reference;
  std::string actor_reference;
  std::string subject_reference;
  std::string rule_reference;
  std::string value_reference;
  Operation operation{Operation::Validate};
};

struct Result {
  bool accepted{false};
  std::string validation_reference;
};

class Provider {
 public:
  virtual ~Provider() = default;
  virtual Result apply(const Request&) = 0;
};

Result execute(const Request&, Provider&);

} // namespace work_disk::tools::bot35
