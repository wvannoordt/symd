#pragma once

#include <concepts>
#include <type_traits>

#include "bin_ops.h"
#include "zero.h"

namespace symd
{
    template <typename func_t, const symbol_t var_id>
    requires (!var_list_contains<typename func_t::variable_t,var_id>::value)
    zero_t ddx_single_valued(const func_t& func, const var_t<var_id>& var)
    {
        return zero_t();
    }
    
    template <typename func_t, const symbol_t var_id>
    requires (var_list_contains<typename func_t::variable_t,var_id>::value)
    auto ddx_single_valued(const func_t& func, const var_t<var_id>& var)
    {
        return func. template differentiate<var_id>();
    }
    
    template <typename func_t, const symbol_t var_id> auto ddx(const func_t& func, const var_t<var_id>& var)
    {
        return ddx_single_valued(func, var);
    }
}