#pragma once
#include <string>
#include <cstdint>

namespace work_disk::tools::bot24 {

enum class Operation { Block, Mute };

struct Request {
  std::string request_id;
  std::string authority_reference;
  std::string actor_reference;
  std::string target_reference;
  Operation operation;
  std::int64_t expected_version{-1};
};

struct Result {
  bool accepted{false};
  std::string relationship_reference;
};

class Provider {
 public:
  virtual ~Provider() = default;
  virtual Result apply(const Request& request) = 0;
};

Result execute(const Request& request, Provider& provider);

} // namespace work_disk::tools::bot24
