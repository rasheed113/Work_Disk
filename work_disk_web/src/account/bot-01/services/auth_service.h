#ifndef WORK_DISK_AUTH_SERVICE_H
#define WORK_DISK_AUTH_SERVICE_H

#include "../models/account_model.h"
#include "../repositories/account_repository.h"
#include "../repositories/saved_account_repository.h"
#include "session_service.h"

#include <string>

namespace work_disk::account {

class AuthService {
public:
    AuthService(
        AccountRepository& accountRepository,
        SavedAccountRepository& savedAccountRepository,
        SessionService& sessionService
    );

    bool signupWithEmail(
        const std::string& id,
        const std::string& email
    );

    bool loginWithEmail(
        const std::string& email,
        const std::string& password
    );

    bool logout();

    bool forgotPassword(const std::string& email);

    bool resetPassword(
        const std::string& email,
        const std::string& resetToken,
        const std::string& newPassword
    );

    bool loginWithGoogle(const std::string& providerToken);

    bool loginWithFacebook(const std::string& providerToken);

    bool switchAccount(const std::string& accountId);

    bool removeSavedAccount(const std::string& accountId);

    bool isLoggedIn() const;

    const Session& currentSession() const;

private:
    AccountRepository& accountRepository_;
    SavedAccountRepository& savedAccountRepository_;
    SessionService& sessionService_;
};

} // namespace work_disk::account

#endif
