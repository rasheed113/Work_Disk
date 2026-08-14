#include "../../../../src/account/bot-01/models/saved_account_model.h"
#include "../../../../src/account/bot-01/repositories/saved_account_repository.h"

#include <cassert>

using work_disk::account::SavedAccount;
using work_disk::account::SavedAccountRepository;

int main() {
    SavedAccountRepository repository;

    assert(!repository.exists("account-001"));
    assert(!repository.exists("account-002"));

    SavedAccount accountA(
        "account-001",
        "user-a@example.com"
    );

    SavedAccount accountB(
        "account-002",
        "user-b@example.com"
    );

    assert(repository.save(accountA));
    assert(repository.save(accountB));

    assert(repository.exists("account-001"));
    assert(repository.exists("account-002"));

    auto loadedA = repository.findByAccountId("account-001");
    auto loadedB = repository.findByAccountId("account-002");

    assert(loadedA.accountId() == "account-001");
    assert(loadedA.displayEmail() == "user-a@example.com");

    assert(loadedB.accountId() == "account-002");
    assert(loadedB.displayEmail() == "user-b@example.com");

    assert(repository.remove("account-001"));
    assert(!repository.exists("account-001"));

    assert(repository.exists("account-002"));

    assert(!repository.remove("account-999"));

    return 0;
}
