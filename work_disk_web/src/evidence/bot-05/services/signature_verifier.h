#pragma once

#include "../models/evidence_model.h"

namespace work_disk::evidence::bot_05 {

class SignatureVerifier {
 public:
  virtual ~SignatureVerifier() = default;
  virtual bool verify(const EvidenceArtifact& evidence) const = 0;
};

}  // namespace work_disk::evidence::bot_05
