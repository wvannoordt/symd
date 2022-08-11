#pragma once

#include "var_list.h"
#include "constant.h"
#include "forward_expression.h"
#include "zero.h"

namespace symd
{
    enum binary_operation
    {
        op_sum,
        op_difference,
        op_product,
        op_quotient
    };
    
    template <typename lhs_t, typename rhs_t, const binary_operation bin_op, const symbol_t var_id>
    requires (bin_op == op_sum)
    auto differentiate_binary_operation(const lhs_t& lhs, const rhs_t& rhs)
    {
        return lhs. template differentiate<var_id>() + rhs. template differentiate<var_id>();
    }
    
    template <typename lhs_t, typename rhs_t, const binary_operation bin_op, const symbol_t var_id>
    requires (bin_op == op_difference)
    auto differentiate_binary_operation(const lhs_t& lhs, const rhs_t& rhs)
    {
        return lhs. template differentiate<var_id>() - rhs. template differentiate<var_id>();
    }
    
    template <typename lhs_t, typename rhs_t, const binary_operation bin_op, const symbol_t var_id>
    requires (bin_op == op_product)
    auto differentiate_binary_operation(const lhs_t& lhs, const rhs_t& rhs)
    {
        return lhs. template differentiate<var_id>()*rhs + rhs. template differentiate<var_id>()*lhs;
    }
    
    template <typename lhs_t, typename rhs_t, const binary_operation bin_op, const symbol_t var_id>
    requires (bin_op == op_quotient)
    auto differentiate_binary_operation(const lhs_t& lhs, const rhs_t& rhs)
    {
        return ((lhs. template differentiate<var_id>())*rhs - (rhs. template differentiate<var_id>())*lhs)/(rhs*rhs);
    }
    
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
        
        template <const symbol_t var_id> 
        requires (!var_list_contains<variable_t, var_id>::value)
        zero_t differentiate(void) const
        {
            return zero_t();
        }
        
        template <const symbol_t var_id> 
        requires (var_list_contains<variable_t, var_id>::value)
        auto differentiate(void) const
        {
            return differentiate_binary_operation<lhs_t, rhs_t, bin_op, var_id>(lhs, rhs);
        }
        
        template <typename rhs_exp_t>
        constexpr auto operator +(const rhs_exp_t& rhs_exp)
        {
            typedef typename forward_expression_t<rhs_exp_t>::type base_t;
            return binary_operation_t<binary_operation_t, base_t, op_sum>(*this, forward_expression(rhs_exp));
        }
        
        template <typename rhs_exp_t>
        constexpr auto operator -(const rhs_exp_t& rhs_exp)
        {
            typedef typename forward_expression_t<rhs_exp_t>::type base_t;
            return binary_operation_t<binary_operation_t, base_t, op_difference>(*this, forward_expression(rhs_exp));
        }
        
        template <typename rhs_exp_t>
        constexpr auto operator *(const rhs_exp_t& rhs_exp)
        {
            typedef typename forward_expression_t<rhs_exp_t>::type base_t;
            return binary_operation_t<binary_operation_t, base_t, op_product>(*this, forward_expression(rhs_exp));
        }
        
        template <typename rhs_exp_t>
        constexpr auto operator /(const rhs_exp_t& rhs_exp)
        {
            typedef typename forward_expression_t<rhs_exp_t>::type base_t;
            return binary_operation_t<binary_operation_t, base_t, op_quotient>(*this, forward_expression(rhs_exp));
        }
    };
    
    template <typename lhs_exp_t, typename bin_lhs_t, typename bin_rhs_t, const binary_operation bin_op>
    auto operator +(const lhs_exp_t& lhs_exp, const binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>& rhs_exp)
    {
        using base_t = typename forward_expression_t<lhs_exp_t>::type;
        using arg_t = binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>;
        return binary_operation_t<base_t, arg_t, op_sum>(forward_expression(lhs_exp), rhs_exp);
    }
    
    template <typename lhs_exp_t, typename bin_lhs_t, typename bin_rhs_t, const binary_operation bin_op>
    auto operator -(const lhs_exp_t& lhs_exp, const binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>& rhs_exp)
    {
        using base_t = typename forward_expression_t<lhs_exp_t>::type;
        using arg_t = binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>;
        return binary_operation_t<base_t, arg_t, op_difference>(forward_expression(lhs_exp), rhs_exp);
    }
    
    template <typename lhs_exp_t, typename bin_lhs_t, typename bin_rhs_t, const binary_operation bin_op>
    auto operator *(const lhs_exp_t& lhs_exp, const binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>& rhs_exp)
    {
        using base_t = typename forward_expression_t<lhs_exp_t>::type;
        using arg_t = binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>;
        return binary_operation_t<base_t, arg_t, op_product>(forward_expression(lhs_exp), rhs_exp);
    }
    
    template <typename lhs_exp_t, typename bin_lhs_t, typename bin_rhs_t, const binary_operation bin_op>
    auto operator /(const lhs_exp_t& lhs_exp, const binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>& rhs_exp)
    {
        using base_t = typename forward_expression_t<lhs_exp_t>::type;
        using arg_t = binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>;
        return binary_operation_t<base_t, arg_t, op_quotient>(forward_expression(lhs_exp), rhs_exp);
    }
}