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
    
    template <typename lhs_t, typename rhs_t, const binary_operation bin_op> struct binary_operation_t
    {
        typedef typename var_list_union
        <
            typename lhs_t::variable_t,
            typename rhs_t::variable_t
        >::type variable_t;
        lhs_t lhs;
        rhs_t rhs;
        binary_operation_t(){}
        binary_operation_t(const lhs_t& lhs_in, const rhs_t& rhs_in)
        {
            lhs = lhs_in;
            rhs = rhs_in;
        }
        
        template <typename rhs_exp_t> auto operator +(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, rhs_exp_t, op_sum>(*this, rhs_exp);
        }
        
        template <typename rhs_exp_t> auto operator -(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, rhs_exp_t, op_difference>(*this, rhs_exp);
        }
        
        template <typename rhs_exp_t> auto operator *(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, rhs_exp_t, op_product>(*this, rhs_exp);
        }
        
        template <typename rhs_exp_t> auto operator /(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, rhs_exp_t, op_quotient>(*this, rhs_exp);
        }
    };
}