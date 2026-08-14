#include "../../../../src/account/bot-01/models/account_model.h"
#include "../../../../src/account/bot-01/repositories/account_repository.h"
#include "../../../../src/account/bot-01/services/account_service.h"

#include <cassert>

using work_disk::account::AccountRepository;
using work_disk::account::AccountService;

int main() {
    AccountRepository repository;
    AccountService service(repository);

    assert(service.createAccount(
        "account-001",
        "user@example.com"
    ));

    assert(!service.createAccount(
        "account-001",
        "another@example.com"
    ));

    assert(!service.createAccount(
        "",
        "invalid@example.com"
    ));

    assert(!service.createAccount(
        "account-002",
        "invalid-email"
    ));

    auto account = service.getAccount("account-001");

    assert(account.id() == "account-001");
    assert(account.email() == "user@example.com");

    auto missing = service.getAccount("account-999");

    assert(missing.id().empty());
    assert(missing.email().empty());

    return 0;
}
