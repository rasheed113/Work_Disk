#include "../../../../src/account/bot-01/models/account_model.h"
#include "../../../../src/account/bot-01/models/saved_account_model.h"
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

    // Signup Account A.
    assert(auth.signupWithEmail(
        "account-001",
        "user-a@example.com"
    ));

    // Signup Account B.
    assert(auth.signupWithEmail(
        "account-002",
        "user-b@example.com"
    ));

    // Duplicate account rejected.
    assert(!auth.signupWithEmail(
        "account-001",
        "another@example.com"
    ));

    // Both accounts remain available.
    assert(savedAccountRepository.exists("account-001"));
    assert(savedAccountRepository.exists("account-002"));

    // Account A becomes active.
    assert(sessionService.startSession("account-001"));
    assert(auth.isLoggedIn());
    assert(auth.currentSession().accountId() == "account-001");

    // Switch to Account B.
    assert(auth.switchAccount("account-002"));
    assert(auth.isLoggedIn());
    assert(auth.currentSession().accountId() == "account-002");

    // Account A is still saved.
    assert(savedAccountRepository.exists("account-001"));

    // Switch back to Account A.
    assert(auth.switchAccount("account-001"));
    assert(auth.currentSession().accountId() == "account-001");

    // Logout.
    assert(auth.logout());
    assert(!auth.isLoggedIn());

    // Logout does NOT remove saved accounts.
    assert(savedAccountRepository.exists("account-001"));
    assert(savedAccountRepository.exists("account-002"));

    // Saved account can be explicitly removed.
    assert(auth.removeSavedAccount("account-002"));
    assert(!savedAccountRepository.exists("account-002"));

    // Account A remains.
    assert(savedAccountRepository.exists("account-001"));

    return 0;
}
