#pragma once
#include <string>
#include <vector>

namespace work_disk::tools::bot34 {

enum class MatchMode { Exact, Prefix, Token };

struct Query {
  std::string request_id;
  std::string authority_reference;
  std::string actor_reference;
  std::string scope_reference;
  std::string text;
  MatchMode mode{MatchMode::Token};
};

struct Result {
  bool accepted{false};
  std::vector<std::string> result_references;
};

class Provider {
 public:
  virtual ~Provider() = default;
  virtual Result search(const Query&) = 0;
};

Result execute(const Query&, Provider&);

} // namespace work_disk::tools::bot34
