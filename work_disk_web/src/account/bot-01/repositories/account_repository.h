#ifndef WORK_DISK_ACCOUNT_REPOSITORY_H
#define WORK_DISK_ACCOUNT_REPOSITORY_H

#include "../models/account_model.h"

#include <string>
#include <unordered_map>

namespace work_disk::account {

class AccountRepository {
public:
    bool save(const Account& account);

    bool exists(const std::string& id) const;

    Account findById(const std::string& id) const;

private:
    std::unordered_map<std::string, Account> accounts_;
};

} // namespace work_disk::account

#endif
