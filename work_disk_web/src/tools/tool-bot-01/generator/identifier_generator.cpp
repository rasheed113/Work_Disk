#include "identifier_generator.h"

#include "identifier_alphabet.h"
#include "../policies/identifier_policy.h"
#include "../randomness/secure_random.h"

#include <cstdint>
#include <stdexcept>
#include <string>

namespace work_disk::tools::bot01 {

std::string IdentifierGenerator::generate(IdentifierType type) {
    const std::size_t length = IdentifierPolicy::length(type);
    const std::string_view alphabet = IdentifierAlphabet::value();

    if (alphabet.empty()) {
        throw std::runtime_error("Identifier alphabet is empty");
    }

    const std::uint16_t alphabet_size =
        static_cast<std::uint16_t>(alphabet.size());

    const std::uint16_t byte_space = 256;

    const std::uint16_t limit =
        static_cast<std::uint16_t>(
            byte_space - (byte_space % alphabet_size)
        );

    std::string identifier;
    identifier.reserve(length);

    while (identifier.size() < length) {
        const auto random_bytes = SecureRandom::bytes(length);

        for (const std::uint8_t byte : random_bytes) {
            if (byte >= limit) {
                continue;
            }

            const std::size_t index =
                static_cast<std::size_t>(byte % alphabet_size);

            identifier.push_back(alphabet[index]);

            if (identifier.size() == length) {
                break;
            }
        }
    }

    return identifier;
}

} // namespace work_disk::tools::bot01
