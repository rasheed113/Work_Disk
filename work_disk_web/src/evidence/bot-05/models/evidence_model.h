#pragma once

#include <cstdint>
#include <string>

namespace work_disk::evidence::bot_05 {

enum class EvidencePurpose {
  Observation,
  ExecutionProof,
  CurrentAuthority,
  ConsumableToken
};

enum class Consumability { Reusable, SingleUse };
enum class Coverage { OutcomeOnly, TransactionLineage, FullTransactionWithConstraints };

enum class SignerEligibility {
  EligibleForHistoricalEvidence,
  EligibleForCurrentAuthority,
  RevokedBeforeIssuance,
  Unknown
};

enum class VerificationStatus { Authoritative, NonAuthoritative };

enum class FailureReason {
  None,
  Malformed,
  InvalidSignature,
  SignerNotEligible,
  LineageMismatch,
  AnchorMissing,
  CoverageInsufficient,
  FreshnessInsufficient,
  RevokedOrSuperseded,
  ContextMismatch,
  PurposeMismatch,
  Conflict,
  AlreadyConsumed,
  ConsumptionBoundaryRequired,
  StateUnavailable
};

struct AuthorityTuple {
  std::string domain;
  std::uint64_t epoch{0};
  std::uint64_t sequence{0};
  std::string state_root;
  std::string lineage_anchor;
};

struct EvidenceArtifact {
  std::string receipt_id;
  std::string signer_id;
  AuthorityTuple authority;
  std::string execution_id;
  std::string subject_id;
  std::string resource_id;
  std::string context_id;
  std::string nonce;
  EvidencePurpose purpose{EvidencePurpose::Observation};
  Coverage coverage{Coverage::OutcomeOnly};
  Consumability consumability{Consumability::Reusable};
  std::string signature;
};

}  // namespace work_disk::evidence::bot_05
