#pragma once

#include "var_list.h"
#include "bin_ops.h"

namespace symd
{
    //CRTP
    template <typename expression_t, typename derived_t> struct unary_operation_t
    {
        expression_t expression;
        
        typedef typename derived_t::variable_t variable_t;
        
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
            return binary_operation_t<derived_t, constant_t<rhs_t>, op_sum>(static_cast<derived_t&>(*this), constant_t<rhs_t>(rhs));
        }
        
        template <typename rhs_t>
        requires (!variate_expression<rhs_t>)
        auto operator-(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, constant_t<rhs_t>, op_difference>(static_cast<derived_t&>(*this), constant_t<rhs_t>(rhs));
        }
        
        template <typename rhs_t>
        requires (!variate_expression<rhs_t>)
        auto operator*(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, constant_t<rhs_t>, op_product>(static_cast<derived_t&>(*this), constant_t<rhs_t>(rhs));
        }
        
        template <typename rhs_t>
        requires (!variate_expression<rhs_t>)
        auto operator/(const rhs_t& rhs)
        {
            return binary_operation_t<derived_t, constant_t<rhs_t>, op_quotient>(static_cast<derived_t&>(*this), constant_t<rhs_t>(rhs));
        }
    };
}