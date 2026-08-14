#include "account_validator.h"

namespace work_disk::account {

bool AccountValidator::isValidId(const std::string& id) {
    return !id.empty();
}

bool AccountValidator::isValidEmail(const std::string& email) {
    if (email.empty()) {
        return false;
    }

    const auto at = email.find('@');

    return at != std::string::npos &&
           at > 0 &&
           at + 1 < email.size();
}

} // namespace work_disk::account
