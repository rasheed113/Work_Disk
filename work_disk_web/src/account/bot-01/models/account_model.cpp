#include "account_model.h"

#include <utility>

namespace work_disk::account {

Account::Account(std::string id, std::string email)
    : id_(std::move(id)),
      email_(std::move(email)) {}

const std::string& Account::id() const {
    return id_;
}

const std::string& Account::email() const {
    return email_;
}

void Account::setEmail(std::string email) {
    email_ = std::move(email);
}

} // namespace work_disk::account
