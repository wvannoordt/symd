#pragma once

#include <concepts>
#include <type_traits>

#include "bin_ops.h"
#include "zero.h"

namespace symd
{
    template <const std::size_t order=1, typename func_t, const symbol_t var_id>
    requires (!var_list_contains<typename func_t::variable_t,var_id>::value)
    zero_t ddx_single_valued(const func_t& func, const var_t<var_id>& var)
    {
        return zero_t();
    }
    
    template <const std::size_t order=1, typename func_t, const symbol_t var_id>
    requires (var_list_contains<typename func_t::variable_t,var_id>::value)
    auto ddx_single_valued(const func_t& func, const var_t<var_id>& var)
    {
        return func. template differentiate<var_id>();
    }
    
    template <const std::size_t order, typename func_t, const symbol_t var_id>
    requires (order == 1)
    auto ddx(const func_t& func, const var_t<var_id>& var)
    {
        return ddx_single_valued(func, var);
    }
    
    template <const std::size_t order, typename func_t, const symbol_t var_id>
    requires (order > 1)
    auto ddx(const func_t& func, const var_t<var_id>& var)
    {
        return ddx<1>(ddx<order-1>(func, var), var);
    }
}