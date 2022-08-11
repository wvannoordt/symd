#pragma once

#include "sym_type.h"

namespace symd
{
    //to be refined later
    template <typename T> concept assignable_numeric_type     = std::is_arithmetic<T>::value;
    template <typename T> concept assignable_expression_type  = variate_expression<T>;
    template <typename T> concept valid_assignment_type       = assignable_numeric_type<T> || assignable_expression_type<T>;
    
    
    template <const symbol_t var_id, typename assigned_t> struct assignment_t
    {
        assigned_t value;
        assignment_t(const assigned_t& value_in) { value = value_in; }
        assignment_t() {}
    };
}