#include "type.hpp"

#include <array>
#include <unordered_map>

namespace token {

    // Array mapping enum values to their string representations
    constexpr std::
        array<std::string_view, static_cast<size_t>(type::RETURN) + 1>
            tokenTypeStrings = {
#define X(name, str) str,
                TOKEN_LIST
#undef X
    };

    // Stream insertion operator using the lookup array
    std::ostream& operator<<(std::ostream& os, type type) {
        auto idx = static_cast<size_t>(type);
        if (idx < tokenTypeStrings.size())
            return os << tokenTypeStrings[idx];
        return os << "Unknown";
    }

    static std::unordered_map<std::string, type> keywords{
        {"fn", type::FUNCTION},
        {"let", type::LET},
        {"if", type::IF},
        {"else", type::ELSE},
        {"true", type::TRUE},
        {"false", type::FALSE},
        {"return", type::RETURN},
    };

    type lookup_identifier(std::string ident) {
        try {
            return keywords.at(ident);
        } catch (const std::out_of_range&) {
            return type::IDENTIFIER;
        }
    }

} // namespace token
