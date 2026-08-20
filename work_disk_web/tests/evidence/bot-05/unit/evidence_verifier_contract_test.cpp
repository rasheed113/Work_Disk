#include "../../../../src/evidence/bot-05/services/evidence_verifier.h"
#include "../../../../src/evidence/bot-05/services/in_memory_consumption_store.h"

#include <cassert>
#include <iostream>

using namespace work_disk::evidence::bot_05;

struct Signature final : SignatureVerifier {
  bool valid{true};
  bool verify(const EvidenceArtifact&) const override { return valid; }
};

struct Registry final : SignerRegistry {
  SignerEligibility eligibility{SignerEligibility::EligibleForHistoricalEvidence};
  bool current{true};
  SignerEligibility eligibilityAtEpoch(
      const std::string&, std::uint64_t) const override { return eligibility; }
  bool currentlyAuthorized(const std::string&) const override { return current; }
};

struct Ledger final : CanonicalStateView {
  bool lineage{true};
  bool current{true};
  bool superseded{false};
  bool fresh{true};
  std::string root{"CANONICAL"};
  bool verifyLineageMembership(const AuthorityTuple&) const override { return lineage; }
  bool isCurrent(const AuthorityTuple&) const override { return current; }
  bool isSuperseded(const AuthorityTuple&) const override { return superseded; }
  bool hasFreshnessCertificate(const AuthorityTuple&) const override { return fresh; }
  std::string currentStateRoot(const std::string&) const override { return root; }
};

static EvidenceArtifact evidence() {
  EvidenceArtifact value;
  value.receipt_id = "R1";
  value.signer_id = "S1";
  value.authority = {"D", 7, 100, "ROOT1", "ANCHOR0"};
  value.execution_id = "E1";
  value.subject_id = "SUB";
  value.resource_id = "RES";
  value.context_id = "CTX";
  value.nonce = "N1";
  value.purpose = EvidencePurpose::ExecutionProof;
  value.coverage = Coverage::FullTransactionWithConstraints;
  value.consumability = Consumability::Reusable;
  value.signature = "SIG";
  return value;
}

static VerificationRequest request(EvidenceArtifact value) {
  return {value, EvidencePurpose::ExecutionProof, Coverage::TransactionLineage,
          "D", "SUB", "RES", "CTX", false, false};
}

static void expectFailure(FailureReason reason, EvidenceVerifier& verifier,
                          VerificationRequest value) {
  assert(verifier.verify(value).reason == reason);
}

int main() {
  Signature signature;
  Registry registry;
  Ledger ledger;
  EvidenceVerifier verifier(signature, registry, ledger);

  assert(verifier.verify(request(evidence())).authoritative());

  signature.valid = false;
  expectFailure(FailureReason::InvalidSignature, verifier, request(evidence()));
  signature.valid = true;

  registry.eligibility = SignerEligibility::RevokedBeforeIssuance;
  expectFailure(FailureReason::SignerNotEligible, verifier, request(evidence()));
  registry.eligibility = SignerEligibility::EligibleForHistoricalEvidence;

  ledger.lineage = false;
  expectFailure(FailureReason::LineageMismatch, verifier, request(evidence()));
  ledger.lineage = true;

  auto narrow = evidence();
  narrow.coverage = Coverage::OutcomeOnly;
  auto narrow_request = request(narrow);
  narrow_request.required_coverage = Coverage::FullTransactionWithConstraints;
  expectFailure(FailureReason::CoverageInsufficient, verifier, narrow_request);

  auto wrong_context = evidence();
  wrong_context.context_id = "OTHER";
  expectFailure(FailureReason::ContextMismatch, verifier, request(wrong_context));

  auto wrong_purpose = evidence();
  wrong_purpose.purpose = EvidencePurpose::Observation;
  expectFailure(FailureReason::PurposeMismatch, verifier, request(wrong_purpose));

  auto current_request = request(evidence());
  current_request.require_current_authority = true;
  ledger.superseded = true;
  expectFailure(FailureReason::RevokedOrSuperseded, verifier, current_request);
  ledger.superseded = false;

  ledger.fresh = false;
  expectFailure(FailureReason::RevokedOrSuperseded, verifier, current_request);
  ledger.fresh = true;

  registry.current = false;
  expectFailure(FailureReason::RevokedOrSuperseded, verifier, current_request);
  registry.current = true;

  registry.current = false;
  assert(verifier.verify(request(evidence())).authoritative());
  registry.current = true;

  auto single = evidence();
  single.consumability = Consumability::SingleUse;
  InMemoryConsumptionStore store;
  EvidenceVerifier consuming(signature, registry, ledger, &store);
  auto single_request = request(single);
  expectFailure(FailureReason::ConsumptionBoundaryRequired, consuming, single_request);
  single_request.consume_if_single_use = true;
  assert(consuming.verify(single_request).authoritative());
  expectFailure(FailureReason::AlreadyConsumed, consuming, single_request);

  std::cout << "BOT_05_EVIDENCE_VERIFIER_CONTRACT_TEST=PASS\n";
  return 0;
}
