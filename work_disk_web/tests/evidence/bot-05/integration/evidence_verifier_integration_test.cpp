#include "../../../../src/evidence/bot-05/services/evidence_verifier.h"

#include <cassert>
#include <iostream>

using namespace work_disk::evidence::bot_05;

struct Signature final : SignatureVerifier {
  bool verify(const EvidenceArtifact&) const override { return true; }
};

struct Registry final : SignerRegistry {
  SignerEligibility eligibilityAtEpoch(
      const std::string&, std::uint64_t) const override {
    return SignerEligibility::EligibleForHistoricalEvidence;
  }
  bool currentlyAuthorized(const std::string&) const override { return true; }
};

struct Ledger final : CanonicalStateView {
  bool verifyLineageMembership(const AuthorityTuple& tuple) const override {
    return tuple.domain == "D" && tuple.state_root == "R1" &&
           tuple.lineage_anchor == "A0";
  }
  bool isCurrent(const AuthorityTuple& tuple) const override {
    return tuple.epoch == 7 && tuple.sequence == 100 &&
           tuple.state_root == "R1";
  }
  bool isSuperseded(const AuthorityTuple&) const override { return false; }
  bool hasFreshnessCertificate(const AuthorityTuple&) const override { return true; }
  std::string currentStateRoot(const std::string&) const override { return "R1"; }
};

int main() {
  EvidenceArtifact evidence{
      "R1", "S1", {"D", 7, 100, "R1", "A0"}, "E1", "SUB", "RES", "CTX",
      "N1", EvidencePurpose::ExecutionProof,
      Coverage::FullTransactionWithConstraints, Consumability::Reusable, "SIG"};

  VerificationRequest request{
      evidence, EvidencePurpose::ExecutionProof,
      Coverage::FullTransactionWithConstraints, "D", "SUB", "RES", "CTX",
      true, false};

  Signature signature;
  Registry registry;
  Ledger ledger;
  EvidenceVerifier verifier(signature, registry, ledger);
  const auto result = verifier.verify(request);

  assert(result.authoritative());
  assert(result.canonical_root == "R1");
  assert(result.signature_valid);
  assert(result.lineage_valid);
  assert(result.coverage_sufficient);

  std::cout << "BOT_05_EVIDENCE_VERIFIER_INTEGRATION_TEST=PASS\n";
  return 0;
}
