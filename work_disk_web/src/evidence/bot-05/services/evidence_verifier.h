#pragma once

#include "canonical_state_view.h"
#include "consumption_store.h"
#include "signature_verifier.h"
#include "signer_registry.h"
#include "../models/verification_model.h"

namespace work_disk::evidence::bot_05 {

class EvidenceVerifier {
 public:
  EvidenceVerifier(const SignatureVerifier& signatures,
                   const SignerRegistry& signers,
                   const CanonicalStateView& state,
                   ConsumptionStore* consumption = nullptr);

  VerificationResult verify(const VerificationRequest& request) const;

 private:
  const SignatureVerifier& signatures_;
  const SignerRegistry& signers_;
  const CanonicalStateView& state_;
  ConsumptionStore* consumption_;
};

}  // namespace work_disk::evidence::bot_05
