#pragma once

#include "../models/evidence_model.h"

#include <string>

namespace work_disk::evidence::bot_05 {

class CanonicalStateView {
 public:
  virtual ~CanonicalStateView() = default;
  virtual bool verifyLineageMembership(const AuthorityTuple& tuple) const = 0;
  virtual bool isCurrent(const AuthorityTuple& tuple) const = 0;
  virtual bool isSuperseded(const AuthorityTuple& tuple) const = 0;
  virtual bool hasFreshnessCertificate(const AuthorityTuple& tuple) const = 0;
  virtual std::string currentStateRoot(const std::string& domain) const = 0;
};

}  // namespace work_disk::evidence::bot_05
