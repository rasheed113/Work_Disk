#ifndef WORK_DISK_SAVED_ACCOUNT_MODEL_H
#define WORK_DISK_SAVED_ACCOUNT_MODEL_H

#include <string>

namespace work_disk::account {

class SavedAccount {
public:
    SavedAccount() = default;

    SavedAccount(
        std::string accountId,
        std::string displayEmail
    );

    const std::string& accountId() const;
    const std::string& displayEmail() const;

private:
    std::string accountId_;
    std::string displayEmail_;
};

} // namespace work_disk::account

#endif
