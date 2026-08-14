#include "../../../../src/account/bot-01/models/credential_model.h"
#include "../../../../src/account/bot-01/repositories/credential_repository.h"

#include <cassert>

using work_disk::account::Credential;
using work_disk::account::CredentialRepository;
using work_disk::account::CredentialType;

int main() {
    CredentialRepository repository;

    Credential emailA(
        "account-001",
        CredentialType::EMAIL,
        "user-a@example.com"
    );

    Credential googleA(
        "account-001",
        CredentialType::GOOGLE,
        "google-user-001"
    );

    Credential emailB(
        "account-002",
        CredentialType::EMAIL,
        "user-b@example.com"
    );

    // Save credentials.
    assert(repository.save(emailA));
    assert(repository.save(googleA));
    assert(repository.save(emailB));

    // Same credential cannot be registered twice.
    assert(!repository.save(emailA));

    // Different accounts can have different identifiers.
    assert(repository.exists(
        CredentialType::EMAIL,
        "user-a@example.com"
    ));

    assert(repository.exists(
        CredentialType::EMAIL,
        "user-b@example.com"
    ));

    assert(repository.exists(
        CredentialType::GOOGLE,
        "google-user-001"
    ));

    // Missing credential.
    assert(!repository.exists(
        CredentialType::FACEBOOK,
        "facebook-user-001"
    ));

    // Find by identifier.
    auto foundEmail = repository.findByIdentifier(
        CredentialType::EMAIL,
        "user-a@example.com"
    );

    assert(foundEmail.accountId() == "account-001");
    assert(foundEmail.type() == CredentialType::EMAIL);
    assert(foundEmail.identifier() == "user-a@example.com");

    // Find all credentials belonging to Account A.
    auto accountCredentials =
        repository.findByAccountId("account-001");

    assert(accountCredentials.size() == 2);

    // Account B has only one credential.
    auto accountBCredentials =
        repository.findByAccountId("account-002");

    assert(accountBCredentials.size() == 1);
    assert(
        accountBCredentials[0].identifier()
        == "user-b@example.com"
    );

    // Missing account has no credentials.
    auto missingCredentials =
        repository.findByAccountId("account-999");

    assert(missingCredentials.empty());

    // Remove one credential.
    assert(repository.remove(
        CredentialType::GOOGLE,
        "google-user-001"
    ));

    assert(!repository.exists(
        CredentialType::GOOGLE,
        "google-user-001"
    ));

    // Email credential remains untouched.
    assert(repository.exists(
        CredentialType::EMAIL,
        "user-a@example.com"
    ));

    // Removing a missing credential fails.
    assert(!repository.remove(
        CredentialType::FACEBOOK,
        "facebook-user-999"
    ));

    return 0;
}
