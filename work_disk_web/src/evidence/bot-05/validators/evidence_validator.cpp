#include "evidence_validator.h"

namespace work_disk::evidence::bot_05 {

namespace {
bool nonEmpty(const std::string& value) { return !value.empty(); }
}

bool EvidenceValidator::isStructurallyValid(const EvidenceArtifact& evidence) {
  return nonEmpty(evidence.receipt_id) && nonEmpty(evidence.signer_id) &&
         nonEmpty(evidence.authority.domain) &&
         nonEmpty(evidence.authority.state_root) &&
         nonEmpty(evidence.authority.lineage_anchor) &&
         nonEmpty(evidence.execution_id) && nonEmpty(evidence.nonce) &&
         nonEmpty(evidence.signature);
}

bool EvidenceValidator::coverageSatisfies(Coverage actual, Coverage required) {
  return static_cast<int>(actual) >= static_cast<int>(required);
}

bool EvidenceValidator::contextMatches(const EvidenceArtifact& evidence,
                                       const VerificationRequest& request) {
  return evidence.authority.domain == request.expected_domain &&
         evidence.subject_id == request.expected_subject &&
         evidence.resource_id == request.expected_resource &&
         evidence.context_id == request.expected_context;
}

bool EvidenceValidator::purposeMatches(const EvidenceArtifact& evidence,
                                       const VerificationRequest& request) {
  return evidence.purpose == request.required_purpose;
}

}  // namespace work_disk::evidence::bot_05
