#ifndef WORK_DISK_ACCOUNT_MODEL_H
#define WORK_DISK_ACCOUNT_MODEL_H

#include <string>

namespace work_disk::account {

class Account {
public:
    Account() = default;

    Account(std::string id, std::string email);

    const std::string& id() const;
    const std::string& email() const;

    void setEmail(std::string email);

private:
    std::string id_;
    std::string email_;
};

} // namespace work_disk::account

#endif
