#pragma once

#include "../models/verification_model.h"

namespace work_disk::evidence::bot_05 {

class EvidenceValidator {
 public:
  static bool isStructurallyValid(const EvidenceArtifact& evidence);
  static bool coverageSatisfies(Coverage actual, Coverage required);
  static bool contextMatches(const EvidenceArtifact& evidence,
                             const VerificationRequest& request);
  static bool purposeMatches(const EvidenceArtifact& evidence,
                             const VerificationRequest& request);
};

}  // namespace work_disk::evidence::bot_05
