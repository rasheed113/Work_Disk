#include "auth_service.h"

#include "../validators/account_validator.h"

namespace work_disk::account {

AuthService::AuthService(
    AccountRepository& accountRepository,
    SavedAccountRepository& savedAccountRepository,
    SessionService& sessionService
)
    : accountRepository_(accountRepository),
      savedAccountRepository_(savedAccountRepository),
      sessionService_(sessionService) {}

bool AuthService::signupWithEmail(
    const std::string& id,
    const std::string& email
) {
    if (!AccountValidator::isValidId(id) ||
        !AccountValidator::isValidEmail(email)) {
        return false;
    }

    if (accountRepository_.exists(id)) {
        return false;
    }

    if (!accountRepository_.save(Account(id, email))) {
        return false;
    }

    if (!savedAccountRepository_.save(
            SavedAccount(id, email))) {
        return false;
    }

    return true;
}

bool AuthService::loginWithEmail(
    const std::string& email,
    const std::string& password
) {
    if (email.empty() || password.empty()) {
        return false;
    }

    // Authentication verification remains pending
    // until the current authentication/security contract
    // defines credential verification.
    return false;
}

bool AuthService::logout() {
    return sessionService_.endSession();
}

bool AuthService::forgotPassword(
    const std::string& email
) {
    if (email.empty()) {
        return false;
    }

    // Password recovery flow remains pending
    // until its current contract is defined.
    return false;
}

bool AuthService::resetPassword(
    const std::string& email,
    const std::string& resetToken,
    const std::string& newPassword
) {
    if (email.empty() ||
        resetToken.empty() ||
        newPassword.empty()) {
        return false;
    }

    // Reset-token verification remains pending
    // until its current contract is defined.
    return false;
}

bool AuthService::loginWithGoogle(
    const std::string& providerToken
) {
    if (providerToken.empty()) {
        return false;
    }

    // Provider verification remains pending
    // until the current provider-authentication contract
    // is defined.
    return false;
}

bool AuthService::loginWithFacebook(
    const std::string& providerToken
) {
    if (providerToken.empty()) {
        return false;
    }

    // Provider verification remains pending
    // until the current provider-authentication contract
    // is defined.
    return false;
}

bool AuthService::switchAccount(
    const std::string& accountId
) {
    if (accountId.empty()) {
        return false;
    }

    if (!savedAccountRepository_.exists(accountId)) {
        return false;
    }

    return sessionService_.switchSession(accountId);
}

bool AuthService::removeSavedAccount(
    const std::string& accountId
) {
    if (accountId.empty()) {
        return false;
    }

    return savedAccountRepository_.remove(accountId);
}

bool AuthService::isLoggedIn() const {
    return sessionService_.isLoggedIn();
}

const Session& AuthService::currentSession() const {
    return sessionService_.currentSession();
}

} // namespace work_disk::account
