#include "session_model.h"

#include <utility>

namespace work_disk::account {

Session::Session(std::string accountId)
    : accountId_(std::move(accountId)) {}

const std::string& Session::accountId() const {
    return accountId_;
}

bool Session::isValid() const {
    return !accountId_.empty();
}

} // namespace work_disk::account
