#ifndef WORK_DISK_SAVED_ACCOUNT_REPOSITORY_H
#define WORK_DISK_SAVED_ACCOUNT_REPOSITORY_H

#include "../models/saved_account_model.h"

#include <string>
#include <unordered_map>

namespace work_disk::account {

class SavedAccountRepository {
public:
    bool save(const SavedAccount& account);

    bool exists(const std::string& accountId) const;

    SavedAccount findByAccountId(
        const std::string& accountId
    ) const;

    bool remove(const std::string& accountId);

private:
    std::unordered_map<std::string, SavedAccount> accounts_;
};

} // namespace work_disk::account

#endif
