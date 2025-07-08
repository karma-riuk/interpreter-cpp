namespace parser {
    enum class precedence {
        LOWEST,
        EQUALS,
        LESS_GREATER,
        SUM,
        PRODUCT,
        PREFIX,
        CALL
    };
}
