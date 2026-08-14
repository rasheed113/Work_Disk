#ifndef WORK_DISK_SESSION_SERVICE_H
#define WORK_DISK_SESSION_SERVICE_H

#include "../models/session_model.h"

#include <string>

namespace work_disk::account {

class SessionService {
public:
    bool startSession(const std::string& accountId);

    bool endSession();

    bool switchSession(const std::string& accountId);

    bool isLoggedIn() const;

    const Session& currentSession() const;

private:
    Session session_;
};

} // namespace work_disk::account

#endif
