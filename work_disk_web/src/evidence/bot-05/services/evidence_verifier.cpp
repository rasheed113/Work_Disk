#include "evidence_verifier.h"

#include "../validators/evidence_validator.h"

namespace work_disk::evidence::bot_05 {

EvidenceVerifier::EvidenceVerifier(const SignatureVerifier& signatures,
                                   const SignerRegistry& signers,
                                   const CanonicalStateView& state,
                                   ConsumptionStore* consumption)
    : signatures_(signatures), signers_(signers), state_(state),
      consumption_(consumption) {}

VerificationResult EvidenceVerifier::verify(
    const VerificationRequest& request) const {
  VerificationResult result;
  const auto& evidence = request.evidence;

  if (!EvidenceValidator::isStructurallyValid(evidence)) {
    result.reason = FailureReason::Malformed;
    result.detail = "required evidence fields are missing";
    return result;
  }

  result.signature_valid = signatures_.verify(evidence);
  if (!result.signature_valid) {
    result.reason = FailureReason::InvalidSignature;
    result.detail = "evidence signature is invalid";
    return result;
  }

  const auto eligibility =
      signers_.eligibilityAtEpoch(evidence.signer_id, evidence.authority.epoch);
  result.signer_historically_eligible =
      eligibility == SignerEligibility::EligibleForHistoricalEvidence ||
      eligibility == SignerEligibility::EligibleForCurrentAuthority;
  result.signer_currently_authorized =
      signers_.currentlyAuthorized(evidence.signer_id);

  if (!result.signer_historically_eligible) {
    result.reason = FailureReason::SignerNotEligible;
    result.detail = "signer was not eligible for this evidence at its epoch";
    return result;
  }

  if (!EvidenceValidator::contextMatches(evidence, request)) {
    result.reason = FailureReason::ContextMismatch;
    result.detail = "subject, resource, context, or domain binding mismatch";
    return result;
  }
  result.context_valid = true;

  if (!EvidenceValidator::purposeMatches(evidence, request)) {
    result.reason = FailureReason::PurposeMismatch;
    result.detail = "evidence purpose does not match requested claim";
    return result;
  }
  result.purpose_valid = true;

  if (!EvidenceValidator::coverageSatisfies(evidence.coverage,
                                            request.required_coverage)) {
    result.reason = FailureReason::CoverageInsufficient;
    result.detail = "declared evidence coverage is insufficient";
    return result;
  }
  result.coverage_sufficient = true;

  if (!state_.verifyLineageMembership(evidence.authority)) {
    result.reason = FailureReason::LineageMismatch;
    result.detail = "evidence is not anchored in canonical authoritative lineage";
    return result;
  }
  result.lineage_valid = true;
  result.canonical_root = state_.currentStateRoot(evidence.authority.domain);

  if (request.require_current_authority) {
    if (!result.signer_currently_authorized ||
        state_.isSuperseded(evidence.authority) ||
        !state_.hasFreshnessCertificate(evidence.authority) ||
        !state_.isCurrent(evidence.authority)) {
      result.freshness_valid = false;
      result.reason = FailureReason::RevokedOrSuperseded;
      result.detail =
          "historical evidence does not establish current authority";
      return result;
    }
  }

  if (evidence.consumability == Consumability::SingleUse) {
    if (!request.consume_if_single_use || consumption_ == nullptr) {
      result.reason = FailureReason::ConsumptionBoundaryRequired;
      result.detail =
          "single-use evidence requires an explicit consumption boundary";
      return result;
    }

    if (consumption_->isConsumed(evidence.nonce) ||
        !consumption_->tryConsume(evidence.nonce)) {
      result.reason = FailureReason::AlreadyConsumed;
      result.consumed = true;
      result.detail = "single-use evidence has already been consumed";
      return result;
    }
    result.consumed = true;
  }

  result.status = VerificationStatus::Authoritative;
  result.reason = FailureReason::None;
  result.detail =
      "evidence is authoritative only for the explicitly requested claim";
  return result;
}

}  // namespace work_disk::evidence::bot_05
