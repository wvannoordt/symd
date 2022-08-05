#pragma once

#include "var_list.h"
#include "bin_ops.h"

namespace symd
{
    //CRTP
    template <typename expression_t, typename derived_t> struct unary_operation_t
    {
        expression_t expression;
        
        typedef typename expression_t::variable_t variable_t;
        
        unary_operation_t(){}
        unary_operation_t(const expression_t& expression_in){expression = expression_in;}
        
        //variate expressions
        template <variate_expression rhs_t> auto operator+(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, rhs_t, op_sum>(static_cast<derived_t&>(*this), rhs);
        }
        
        template <variate_expression rhs_t> auto operator-(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, rhs_t, op_difference>(static_cast<derived_t&>(*this), rhs);
        }
        
        template <variate_expression rhs_t> auto operator*(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, rhs_t, op_product>(static_cast<derived_t&>(*this), rhs);
        }
        
        template <variate_expression rhs_t> auto operator/(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, rhs_t, op_quotient>(static_cast<derived_t&>(*this), rhs);
        }
        
        //constant expressions
        template <typename rhs_t>
        requires (!variate_expression<rhs_t>)
        auto operator+(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, constant_t<rhs_t>, op_sum>(static_cast<const derived_t&>(*this), constant_t<rhs_t>(rhs));
        }
        
        template <typename rhs_t>
        requires (!variate_expression<rhs_t>)
        auto operator-(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, constant_t<rhs_t>, op_difference>(static_cast<const derived_t&>(*this), constant_t<rhs_t>(rhs));
        }
        
        template <typename rhs_t>
        requires (!variate_expression<rhs_t>)
        auto operator*(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, constant_t<rhs_t>, op_product>(static_cast<const derived_t&>(*this), constant_t<rhs_t>(rhs));
        }
        
        template <typename rhs_t>
        requires (!variate_expression<rhs_t>)
        auto operator/(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, constant_t<rhs_t>, op_quotient>(static_cast<const derived_t&>(*this), constant_t<rhs_t>(rhs));
        }
    };
    
    template <variate_expression lhs_t, typename expression_t, typename derived_t>
    auto operator +(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        return binary_operation_t<lhs_t, derived_t, op_sum>(lhs, static_cast<const derived_t&>(rhs));
    }
    
    template <typename lhs_t, typename expression_t, typename derived_t>
    requires (!variate_expression<lhs_t>)
    auto operator +(const lhs_t& lhs, const unary_operation_t<expression_t, derived_t>& rhs)
    {
        return binary_operation_t<constant_t<lhs_t>, derived_t, op_sum>(constant_t<lhs_t>(lhs), static_cast<const derived_t&>(rhs));
    }
}