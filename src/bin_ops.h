#pragma once
#include "var_list.h"
#include "constant.h"
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
        
        template <variate_expression rhs_exp_t>
        constexpr auto operator +(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, rhs_exp_t, op_sum>(*this, rhs_exp);
        }
        
        template <variate_expression rhs_exp_t>
        constexpr auto operator -(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, rhs_exp_t, op_difference>(*this, rhs_exp);
        }
        
        template <variate_expression rhs_exp_t>
        constexpr auto operator *(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, rhs_exp_t, op_product>(*this, rhs_exp);
        }
        
        template <variate_expression rhs_exp_t>
        constexpr auto operator /(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, rhs_exp_t, op_quotient>(*this, rhs_exp);
        }
        
        //pod operands
        template <typename rhs_exp_t> requires (!variate_expression<rhs_exp_t>)
        constexpr auto operator +(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, constant_t<rhs_exp_t>, op_sum>(*this, constant_t<rhs_exp_t>(rhs_exp));
        }
        
        template <typename rhs_exp_t> requires (!variate_expression<rhs_exp_t>)
        constexpr auto operator -(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, constant_t<rhs_exp_t>, op_difference>(*this, constant_t<rhs_exp_t>(rhs_exp));
        }
        
        template <typename rhs_exp_t> requires (!variate_expression<rhs_exp_t>)
        constexpr auto operator *(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, constant_t<rhs_exp_t>, op_product>(*this, constant_t<rhs_exp_t>(rhs_exp));
        }
        
        template <typename rhs_exp_t> requires (!variate_expression<rhs_exp_t>)
        constexpr auto operator /(const rhs_exp_t& rhs_exp)
        {
            return binary_operation_t<binary_operation_t, constant_t<rhs_exp_t>, op_quotient>(*this, constant_t<rhs_exp_t>(rhs_exp));
        }
    };
    
    template <typename lhs_exp_t, typename bin_lhs_t, typename bin_rhs_t, const binary_operation bin_op>
    requires (!variate_expression<lhs_exp_t>)
    auto operator +(const lhs_exp_t& lhs_exp, const binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>& rhs_exp)
    {
        using arg_t = binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>;
        return binary_operation_t<constant_t<lhs_exp_t>, arg_t, op_sum>(constant_t<lhs_exp_t>(lhs_exp), rhs_exp);
    }
    
    template <typename lhs_exp_t, typename bin_lhs_t, typename bin_rhs_t, const binary_operation bin_op>
    requires (!variate_expression<lhs_exp_t>)
    auto operator -(const lhs_exp_t& lhs_exp, const binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>& rhs_exp)
    {
        using arg_t = binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>;
        return binary_operation_t<constant_t<lhs_exp_t>, arg_t, op_difference>(constant_t<lhs_exp_t>(lhs_exp), rhs_exp);
    }
    
    template <typename lhs_exp_t, typename bin_lhs_t, typename bin_rhs_t, const binary_operation bin_op>
    requires (!variate_expression<lhs_exp_t>)
    auto operator *(const lhs_exp_t& lhs_exp, const binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>& rhs_exp)
    {
        using arg_t = binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>;
        return binary_operation_t<constant_t<lhs_exp_t>, arg_t, op_product>(constant_t<lhs_exp_t>(lhs_exp), rhs_exp);
    }
    
    template <typename lhs_exp_t, typename bin_lhs_t, typename bin_rhs_t, const binary_operation bin_op>
    requires (!variate_expression<lhs_exp_t>)
    auto operator /(const lhs_exp_t& lhs_exp, const binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>& rhs_exp)
    {
        using arg_t = binary_operation_t<bin_lhs_t, bin_rhs_t, bin_op>;
        return binary_operation_t<constant_t<lhs_exp_t>, arg_t, op_quotient>(constant_t<lhs_exp_t>(lhs_exp), rhs_exp);
    }
}