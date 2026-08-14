#include "account_service.h"

#include "../validators/account_validator.h"

namespace work_disk::account {

AccountService::AccountService(AccountRepository& repository)
    : repository_(repository) {}

bool AccountService::createAccount(
    const std::string& id,
    const std::string& email
) {
    if (!AccountValidator::isValidId(id) ||
        !AccountValidator::isValidEmail(email)) {
        return false;
    }

    if (repository_.exists(id)) {
        return false;
    }

    return repository_.save(Account(id, email));
}

Account AccountService::getAccount(const std::string& id) const {
    if (!AccountValidator::isValidId(id)) {
        return {};
    }

    return repository_.findById(id);
}

} // namespace work_disk::account
