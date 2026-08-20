#pragma once

#include "evidence_model.h"

#include <string>

namespace work_disk::evidence::bot_05 {

struct VerificationRequest {
  EvidenceArtifact evidence;
  EvidencePurpose required_purpose{EvidencePurpose::Observation};
  Coverage required_coverage{Coverage::OutcomeOnly};
  std::string expected_domain;
  std::string expected_subject;
  std::string expected_resource;
  std::string expected_context;
  bool require_current_authority{false};
  bool consume_if_single_use{false};
};

struct VerificationResult {
  VerificationStatus status{VerificationStatus::NonAuthoritative};
  FailureReason reason{FailureReason::None};
  bool signature_valid{false};
  bool signer_historically_eligible{false};
  bool signer_currently_authorized{false};
  bool lineage_valid{false};
  bool coverage_sufficient{false};
  bool freshness_valid{true};
  bool context_valid{false};
  bool purpose_valid{false};
  bool consumed{false};
  std::string canonical_root;
  std::string detail;

  bool authoritative() const {
    return status == VerificationStatus::Authoritative;
  }
};

}  // namespace work_disk::evidence::bot_05
