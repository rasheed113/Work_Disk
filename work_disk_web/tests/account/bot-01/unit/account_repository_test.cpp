#include "../../../../src/account/bot-01/models/account_model.h"
#include "../../../../src/account/bot-01/repositories/account_repository.h"

#include <cassert>

using work_disk::account::Account;
using work_disk::account::AccountRepository;

int main() {
    AccountRepository repository;

    assert(!repository.exists("account-001"));
    assert(!repository.exists("account-002"));

    Account accountA(
        "account-001",
        "user-a@example.com"
    );

    Account accountB(
        "account-002",
        "user-b@example.com"
    );

    assert(repository.save(accountA));
    assert(repository.save(accountB));

    assert(repository.exists("account-001"));
    assert(repository.exists("account-002"));

    Account loadedA = repository.findById("account-001");
    Account loadedB = repository.findById("account-002");

    assert(loadedA.id() == "account-001");
    assert(loadedA.email() == "user-a@example.com");

    assert(loadedB.id() == "account-002");
    assert(loadedB.email() == "user-b@example.com");

    Account missing = repository.findById("account-999");

    assert(missing.id().empty());
    assert(missing.email().empty());

    return 0;
}
