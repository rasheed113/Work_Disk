#include "saved_account_repository.h"

namespace work_disk::account {

bool SavedAccountRepository::save(
    const SavedAccount& account
) {
    if (account.accountId().empty()) {
        return false;
    }

    accounts_[account.accountId()] = account;
    return true;
}

bool SavedAccountRepository::exists(
    const std::string& accountId
) const {
    return accounts_.find(accountId) != accounts_.end();
}

SavedAccount SavedAccountRepository::findByAccountId(
    const std::string& accountId
) const {
    const auto it = accounts_.find(accountId);

    if (it == accounts_.end()) {
        return {};
    }

    return it->second;
}

bool SavedAccountRepository::remove(
    const std::string& accountId
) {
    return accounts_.erase(accountId) > 0;
}

} // namespace work_disk::account
