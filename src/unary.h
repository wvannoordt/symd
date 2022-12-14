#pragma once

#include <cmath>
#include <concepts>

#include "var_list.h"
#include "bin_ops.h"
#include "forward_expression.h"

namespace symd
{
    template <typename T> concept is_unary_op = requires(T t)
    {
        T::is_unary_op;
    };
    //CRTP
    template <typename expression_t, typename derived_t> struct unary_operation_t
    {
        expression_t expression;
        
        typedef typename expression_t::variable_t variable_t;
        constexpr static bool is_unary_op = true;
        unary_operation_t(){}
        unary_operation_t(const expression_t& expression_in){expression = expression_in;}
        
        //variate expressions
        template <typename rhs_t>
        auto operator+(const rhs_t& rhs)
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<derived_t, base_t, op_sum>(static_cast<derived_t&>(*this), forward_expression(rhs));
        }
        
        template <typename rhs_t>
        auto operator-(const rhs_t& rhs)
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<derived_t, base_t, op_difference>(static_cast<derived_t&>(*this), forward_expression(rhs));
        }
        
        template <typename rhs_t>
        auto operator*(const rhs_t& rhs)
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<derived_t, base_t, op_product>(static_cast<derived_t&>(*this), forward_expression(rhs));
        }
        
        template <typename rhs_t>
        auto operator/(const rhs_t& rhs)
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<derived_t, base_t, op_quotient>(static_cast<derived_t&>(*this), forward_expression(rhs));
        }
    };
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    requires (!is_unary_op<lhs_t>)
    auto operator +(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        typedef typename forward_expression_t<lhs_t>::type base_t;
        return binary_operation_t<base_t, derived_t, op_sum>(forward_expression(lhs), static_cast<const derived_t&>(rhs));
    }
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    requires (!is_unary_op<lhs_t>)
    auto operator -(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        typedef typename forward_expression_t<lhs_t>::type base_t;
        return binary_operation_t<base_t, derived_t, op_difference>(forward_expression(lhs), static_cast<const derived_t&>(rhs));
    }
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    requires (!is_unary_op<lhs_t>)
    auto operator *(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        typedef typename forward_expression_t<lhs_t>::type base_t;
        return binary_operation_t<base_t, derived_t, op_product>(forward_expression(lhs), static_cast<const derived_t&>(rhs));
    }
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    requires (!is_unary_op<lhs_t>)
    auto operator /(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        typedef typename forward_expression_t<lhs_t>::type base_t;
        return binary_operation_t<base_t, derived_t, op_quotient>(forward_expression(lhs), static_cast<const derived_t&>(rhs));
    }
}