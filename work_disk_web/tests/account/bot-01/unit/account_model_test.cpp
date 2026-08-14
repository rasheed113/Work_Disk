#include "../../../../src/account/bot-01/models/account_model.h"
#include "../../../../src/account/bot-01/validators/account_validator.h"

#include <cassert>

using work_disk::account::Account;
using work_disk::account::AccountValidator;

int main() {
    Account account("account-001", "user@example.com");

    assert(account.id() == "account-001");
    assert(account.email() == "user@example.com");

    account.setEmail("new@example.com");
    assert(account.email() == "new@example.com");

    assert(AccountValidator::isValidId("account-001"));
    assert(!AccountValidator::isValidId(""));

    assert(AccountValidator::isValidEmail("user@example.com"));
    assert(!AccountValidator::isValidEmail(""));
    assert(!AccountValidator::isValidEmail("invalid-email"));
    assert(!AccountValidator::isValidEmail("@example.com"));
    assert(!AccountValidator::isValidEmail("user@"));

    return 0;
}
