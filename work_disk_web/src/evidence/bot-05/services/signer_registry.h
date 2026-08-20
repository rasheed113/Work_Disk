#pragma once

#include "../models/evidence_model.h"

namespace work_disk::evidence::bot_05 {

class SignerRegistry {
 public:
  virtual ~SignerRegistry() = default;
  virtual SignerEligibility eligibilityAtEpoch(
      const std::string& signer_id, std::uint64_t epoch) const = 0;
  virtual bool currentlyAuthorized(const std::string& signer_id) const = 0;
};

}  // namespace work_disk::evidence::bot_05
