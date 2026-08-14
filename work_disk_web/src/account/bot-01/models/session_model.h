#ifndef WORK_DISK_SESSION_MODEL_H
#define WORK_DISK_SESSION_MODEL_H

#include <string>

namespace work_disk::account {

class Session {
public:
    Session() = default;

    explicit Session(std::string accountId);

    const std::string& accountId() const;
    bool isValid() const;

private:
    std::string accountId_;
};

} // namespace work_disk::account

#endif
