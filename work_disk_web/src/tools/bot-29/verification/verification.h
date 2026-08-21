#pragma once
#include <string>

namespace work_disk::tools::bot29 {

enum class Operation { Verify, Revoke };

struct Request {
  std::string request_id;
  std::string authority_reference;
  std::string subject_reference;
  std::string evidence_reference;
  Operation operation;
};

struct Result { bool accepted{false}; std::string verification_reference; };

class Provider {
 public:
  virtual ~Provider() = default;
  virtual Result apply(const Request&) = 0;
};

Result execute(const Request&, Provider&);

} // namespace work_disk::tools::bot29
