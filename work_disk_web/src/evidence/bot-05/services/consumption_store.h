#pragma once

#include <string>

namespace work_disk::evidence::bot_05 {

class ConsumptionStore {
 public:
  virtual ~ConsumptionStore() = default;
  virtual bool isConsumed(const std::string& nonce) const = 0;
  virtual bool tryConsume(const std::string& nonce) = 0;
};

}  // namespace work_disk::evidence::bot_05
