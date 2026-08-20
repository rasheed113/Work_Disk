#include "in_memory_consumption_store.h"

namespace work_disk::evidence::bot_05 {

bool InMemoryConsumptionStore::isConsumed(const std::string& nonce) const {
  return spent_.count(nonce) != 0;
}

bool InMemoryConsumptionStore::tryConsume(const std::string& nonce) {
  if (nonce.empty()) return false;
  return spent_.insert(nonce).second;
}

}  // namespace work_disk::evidence::bot_05
