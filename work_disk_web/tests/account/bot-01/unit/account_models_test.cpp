#include "../../../../src/account/bot-01/models/account_model.h"
#include "../../../../src/account/bot-01/models/credential_model.h"
#include "../../../../src/account/bot-01/models/saved_account_model.h"
#include "../../../../src/account/bot-01/models/session_model.h"

#include <cassert>

using work_disk::account::Account;
using work_disk::account::Credential;
using work_disk::account::CredentialType;
using work_disk::account::SavedAccount;
using work_disk::account::Session;

int main() {
    Account account("account-001", "user@example.com");

    assert(account.id() == "account-001");
    assert(account.email() == "user@example.com");

    Credential emailCredential(
        "account-001",
        CredentialType::EMAIL,
        "user@example.com"
    );

    assert(emailCredential.accountId() == "account-001");
    assert(emailCredential.type() == CredentialType::EMAIL);
    assert(emailCredential.identifier() == "user@example.com");

    SavedAccount saved(
        "account-001",
        "user@example.com"
    );

    assert(saved.accountId() == "account-001");
    assert(saved.displayEmail() == "user@example.com");

    Session invalidSession;
    assert(!invalidSession.isValid());

    Session session("account-001");

    assert(session.isValid());
    assert(session.accountId() == "account-001");

    return 0;
}
