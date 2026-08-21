#pragma once
#include <string>

namespace work_disk::tools::bot51 {

enum class Capability { Camera, Microphone, Location, MediaLibrary };
enum class Operation { Request, Observe };
enum class AccessState { Granted, Denied, Restricted, Unknown };

struct Request {
  std::string request_id;
  std::string caller_context;
  Capability capability;
  Operation operation;
};

struct Result {
  bool accepted{false};
  AccessState state{AccessState::Unknown};
};

class Provider {
 public:
  virtual ~Provider() = default;
  virtual Result request(const Request&) = 0;
  virtual Result observe(const Request&) = 0;
};

Result execute(const Request&, Provider&);

} // namespace work_disk::tools::bot51
