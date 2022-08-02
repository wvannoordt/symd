#pragma once

#include <type_traits>

#include "bin_ops.h"

namespace symd
{
    template <const std::size_t var_id, typename lhs_t, typename rhs_t> auto ddx(const binary_operation_t<lhs_t, op_sum, rhs_t>& prod)
    {
        return ddx<var_id>(lhs_t()) + ddx<var_id>(lhs_t());
    }
    
    template <const std::size_t var_id, typename lhs_t, typename rhs_t> auto ddx(const binary_operation_t<lhs_t, op_difference, rhs_t>& prod)
    {
        return ddx<var_id>(lhs_t()) - ddx<var_id>(lhs_t());
    }
}