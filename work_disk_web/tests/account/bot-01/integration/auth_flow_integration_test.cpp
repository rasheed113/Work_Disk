#include "../../../../src/account/bot-01/repositories/account_repository.h"
#include "../../../../src/account/bot-01/repositories/saved_account_repository.h"
#include "../../../../src/account/bot-01/services/auth_service.h"
#include "../../../../src/account/bot-01/services/session_service.h"

#include <cassert>

using work_disk::account::AccountRepository;
using work_disk::account::AuthService;
using work_disk::account::SavedAccountRepository;
using work_disk::account::SessionService;

int main() {
    AccountRepository accountRepository;
    SavedAccountRepository savedAccountRepository;
    SessionService sessionService;

    AuthService auth(
        accountRepository,
        savedAccountRepository,
        sessionService
    );

    // Create two independent accounts.
    assert(auth.signupWithEmail(
        "account-001",
        "user-a@example.com"
    ));

    assert(auth.signupWithEmail(
        "account-002",
        "user-b@example.com"
    ));

    // Both accounts must exist independently.
    assert(accountRepository.exists("account-001"));
    assert(accountRepository.exists("account-002"));

    assert(savedAccountRepository.exists("account-001"));
    assert(savedAccountRepository.exists("account-002"));

    // Start Account A.
    assert(sessionService.startSession("account-001"));
    assert(auth.isLoggedIn());
    assert(auth.currentSession().accountId() == "account-001");

    // Switch to Account B without destroying Account A.
    assert(auth.switchAccount("account-002"));
    assert(auth.currentSession().accountId() == "account-002");

    assert(accountRepository.exists("account-001"));
    assert(savedAccountRepository.exists("account-001"));

    // Switch back to Account A.
    assert(auth.switchAccount("account-001"));
    assert(auth.currentSession().accountId() == "account-001");

    // Logout only ends the active session.
    assert(auth.logout());
    assert(!auth.isLoggedIn());

    // Account data remains intact after logout.
    assert(accountRepository.exists("account-001"));
    assert(accountRepository.exists("account-002"));

    assert(savedAccountRepository.exists("account-001"));
    assert(savedAccountRepository.exists("account-002"));

    return 0;
}
