#include "session_service.h"

namespace work_disk::account {

bool SessionService::startSession(
    const std::string& accountId
) {
    if (accountId.empty()) {
        return false;
    }

    if (session_.isValid()) {
        return false;
    }

    session_ = Session(accountId);
    return true;
}

bool SessionService::endSession() {
    if (!session_.isValid()) {
        return false;
    }

    session_ = Session();
    return true;
}

bool SessionService::switchSession(
    const std::string& accountId
) {
    if (accountId.empty()) {
        return false;
    }

    if (!session_.isValid()) {
        return startSession(accountId);
    }

    session_ = Session(accountId);
    return true;
}

bool SessionService::isLoggedIn() const {
    return session_.isValid();
}

const Session& SessionService::currentSession() const {
    return session_;
}

} // namespace work_disk::account
