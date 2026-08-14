#include "account_repository.h"

namespace work_disk::account {

bool AccountRepository::save(const Account& account) {
    if (account.id().empty()) {
        return false;
    }

    accounts_[account.id()] = account;
    return true;
}

bool AccountRepository::exists(const std::string& id) const {
    return accounts_.find(id) != accounts_.end();
}

Account AccountRepository::findById(const std::string& id) const {
    const auto it = accounts_.find(id);

    if (it == accounts_.end()) {
        return {};
    }

    return it->second;
}

} // namespace work_disk::account
