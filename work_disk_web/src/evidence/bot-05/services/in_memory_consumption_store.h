#pragma once

#include "consumption_store.h"

#include <unordered_set>

namespace work_disk::evidence::bot_05 {

class InMemoryConsumptionStore final : public ConsumptionStore {
 public:
  bool isConsumed(const std::string& nonce) const override;
  bool tryConsume(const std::string& nonce) override;

 private:
  std::unordered_set<std::string> spent_;
};

}  // namespace work_disk::evidence::bot_05
