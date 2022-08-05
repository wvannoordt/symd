#pragma once

#include "var_list.h"
#include "bin_ops.h"

namespace symd
{
    template <const std::size_t var_id> struct var_t
    {
        typedef typename make_var_list_t<var_id>::type variable_t;
        
        template <variate_expression rhs_t> auto operator+ (const rhs_t& rhs)
        {
            return binary_operation_t<var_t<var_id>, rhs_t, op_sum>(*this, rhs);
        }
        template <variate_expression rhs_t> auto operator- (const rhs_t& rhs)
        {
            return binary_operation_t<var_t<var_id>, rhs_t, op_difference>(*this, rhs);
        }
        template <variate_expression rhs_t> auto operator* (const rhs_t& rhs)
        {
            return binary_operation_t<var_t<var_id>, rhs_t, op_product>(*this, rhs);
        }
        template <variate_expression rhs_t> auto operator/ (const rhs_t& rhs)
        {
            return binary_operation_t<var_t<var_id>, rhs_t, op_quotient>(*this, rhs);
        }
    };
    
    // template <typename lhs_t>//hers
}