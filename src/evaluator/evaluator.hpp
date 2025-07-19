#pragma once

#include "ast/ast.hpp"
#include "object/object.hpp"

namespace eval {
    object::object* eval(ast::node*);
} // namespace eval
