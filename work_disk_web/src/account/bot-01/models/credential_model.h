#ifndef WORK_DISK_CREDENTIAL_MODEL_H
#define WORK_DISK_CREDENTIAL_MODEL_H

#include <string>

namespace work_disk::account {

enum class CredentialType {
    EMAIL,
    GOOGLE,
    FACEBOOK
};

class Credential {
public:
    Credential() = default;

    Credential(
        std::string accountId,
        CredentialType type,
        std::string identifier
    );

    const std::string& accountId() const;
    CredentialType type() const;
    const std::string& identifier() const;

private:
    std::string accountId_;
    CredentialType type_ = CredentialType::EMAIL;
    std::string identifier_;
};

} // namespace work_disk::account

#endif
