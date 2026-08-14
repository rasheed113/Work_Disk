#ifndef WORK_DISK_ACCOUNT_SERVICE_H
#define WORK_DISK_ACCOUNT_SERVICE_H

#include "../models/account_model.h"
#include "../repositories/account_repository.h"

#include <string>

namespace work_disk::account {

class AccountService {
public:
    explicit AccountService(AccountRepository& repository);

    bool createAccount(
        const std::string& id,
        const std::string& email
    );

    Account getAccount(const std::string& id) const;

private:
    AccountRepository& repository_;
};

} // namespace work_disk::account

#endif
