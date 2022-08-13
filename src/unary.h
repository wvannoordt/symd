#pragma once

#include <cmath>

#include "var_list.h"
#include "bin_ops.h"
#include "forward_expression.h"

namespace symd
{
    //CRTP
    template <typename expression_t, typename derived_t> struct unary_operation_t
    {
        expression_t expression;
        
        typedef typename expression_t::variable_t variable_t;
        
        unary_operation_t(){}
        unary_operation_t(const expression_t& expression_in){expression = expression_in;}
        
        template <const symbol_t var_id> 
        requires (!var_list_contains<variable_t, var_id>::value)
        zero_t differentiate(void) const
        {
            return zero_t();
        }
        
        //variate expressions
        template <typename rhs_t> auto operator+(const rhs_t& rhs)
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<derived_t, base_t, op_sum>(static_cast<derived_t&>(*this), forward_expression(rhs));
        }
        
        template <typename rhs_t> auto operator-(const rhs_t& rhs)
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<derived_t, base_t, op_difference>(static_cast<derived_t&>(*this), forward_expression(rhs));
        }
        
        template <typename rhs_t> auto operator*(const rhs_t& rhs)
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<derived_t, base_t, op_product>(static_cast<derived_t&>(*this), forward_expression(rhs));
        }
        
        template <typename rhs_t> auto operator/(const rhs_t& rhs)
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<derived_t, base_t, op_quotient>(static_cast<derived_t&>(*this), forward_expression(rhs));
        }
    };
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    auto operator +(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        typedef typename forward_expression_t<lhs_t>::type base_t;
        return binary_operation_t<base_t, derived_t, op_sum>(forward_expression(lhs), static_cast<const derived_t&>(rhs));
    }
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    auto operator -(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        typedef typename forward_expression_t<lhs_t>::type base_t;
        return binary_operation_t<base_t, derived_t, op_difference>(forward_expression(lhs), static_cast<const derived_t&>(rhs));
    }
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    auto operator *(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        typedef typename forward_expression_t<lhs_t>::type base_t;
        return binary_operation_t<base_t, derived_t, op_product>(forward_expression(lhs), static_cast<const derived_t&>(rhs));
    }
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    auto operator /(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        typedef typename forward_expression_t<lhs_t>::type base_t;
        return binary_operation_t<base_t, derived_t, op_quotient>(forward_expression(lhs), static_cast<const derived_t&>(rhs));
    }
}