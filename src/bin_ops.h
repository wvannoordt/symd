#pragma once
#include "var_list.h"
namespace symd
{
    enum binary_operation
    {
        op_sum,
        op_difference,
        op_product,
        op_quotient
    };
    
    template <typename lhs_t, const binary_operation bin_op, typename rhs_t> struct binary_operation_t
    {
        
    };
    
    template <typename lhs_t, typename rhs_t> struct binary_operation_t<lhs_t, op_sum, rhs_t>
    {
        using deriv_t = lhs_t;
    };
}