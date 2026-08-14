#include "../../../../src/account/bot-01/services/session_service.h"

#include <cassert>

using work_disk::account::SessionService;

int main() {
    SessionService session;

    // No active session initially.
    assert(!session.isLoggedIn());
    assert(session.currentSession().accountId().empty());

    // Account A logs in.
    assert(session.startSession("account-001"));
    assert(session.isLoggedIn());
    assert(session.currentSession().accountId() == "account-001");

    // Starting another session directly is not allowed.
    assert(!session.startSession("account-002"));
    assert(session.currentSession().accountId() == "account-001");

    // Switch from Account A to Account B.
    assert(session.switchSession("account-002"));
    assert(session.isLoggedIn());
    assert(session.currentSession().accountId() == "account-002");

    // Switch back to Account A.
    assert(session.switchSession("account-001"));
    assert(session.currentSession().accountId() == "account-001");

    // Invalid account identifier is rejected.
    assert(!session.switchSession(""));
    assert(session.currentSession().accountId() == "account-001");

    // Logout.
    assert(session.endSession());
    assert(!session.isLoggedIn());
    assert(session.currentSession().accountId().empty());

    // Cannot logout twice.
    assert(!session.endSession());

    // Session can be started again after logout.
    assert(session.startSession("account-002"));
    assert(session.isLoggedIn());
    assert(session.currentSession().accountId() == "account-002");

    return 0;
}
