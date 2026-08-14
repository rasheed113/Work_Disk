#include "saved_account_model.h"

#include <utility>

namespace work_disk::account {

SavedAccount::SavedAccount(
    std::string accountId,
    std::string displayEmail
)
    : accountId_(std::move(accountId)),
      displayEmail_(std::move(displayEmail)) {}

const std::string& SavedAccount::accountId() const {
    return accountId_;
}

const std::string& SavedAccount::displayEmail() const {
    return displayEmail_;
}

} // namespace work_disk::account
