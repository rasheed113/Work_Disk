#ifndef WORK_DISK_ACCOUNT_VALIDATOR_H
#define WORK_DISK_ACCOUNT_VALIDATOR_H

#include <string>

namespace work_disk::account {

class AccountValidator {
public:
    static bool isValidId(const std::string& id);
    static bool isValidEmail(const std::string& email);
};

} // namespace work_disk::account

#endif
