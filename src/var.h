#pragma once

#include "var_list.h"
#include "zero.h"
#include "bin_ops.h"
#include "assignment.h"
#include "unity.h"
#include "forward_expression.h"

namespace symd
{
    template <typename T> concept basic_variable = requires(T t)
    {
        T::var_value();
    };
    
    template <const symbol_t var_id> struct var_t
    {
        constexpr static symbol_t var_value() { return var_id; }
        typedef typename make_var_list_t<var_id>::type variable_t;
        
        template <typename rhs_t> auto operator+ (const rhs_t& rhs) const
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<var_t<var_id>, base_t, op_sum>(*this, forward_expression(rhs));
        }
        template <typename rhs_t> auto operator- (const rhs_t& rhs) const
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<var_t<var_id>, base_t, op_difference>(*this, forward_expression(rhs));
        }
        template <typename rhs_t> auto operator* (const rhs_t& rhs) const
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<var_t<var_id>, base_t, op_product>(*this, forward_expression(rhs));
        }
        template <typename rhs_t> auto operator/ (const rhs_t& rhs) const
        {
            typedef typename forward_expression_t<rhs_t>::type base_t;
            return binary_operation_t<var_t<var_id>, base_t, op_quotient>(*this, forward_expression(rhs));
        }
        
        template <const symbol_t var_id_in> 
        requires (var_id_in != var_id)
        zero_t differentiate() const
        {
            return zero_t();
        }
        
        template <const symbol_t var_id_in> 
        requires (var_id_in == var_id)
        unity_t differentiate() const
        {
            return unity_t();
        }
        
        template <valid_assignment_type assigned_t> assignment_t<var_id, assigned_t> operator=(const assigned_t& rhs) const
        {
            return assignment_t<var_id,assigned_t>(rhs);
        }
        
        template <typename... assignments_t>
        requires (contains_assignment_for<var_id, assignments_t...>())
        auto operator()(assignments_t... assignments) const
        {
            return fetch_assignment_value<var_id, assignments_t...>(assignments...);
        }
        
        template <typename... assignments_t>
        requires (!contains_assignment_for<var_id, assignments_t...>())
        const var_t<var_id>& operator()(assignments_t... assignments) const
        {
            return *this;
        }
    };
    
    template <variate_expression lhs_t, const std::size_t var_id> auto operator +(const lhs_t& lhs, const var_t<var_id>& rhs)
    {
        return binary_operation_t<lhs_t, var_t<var_id>, op_sum>(lhs, rhs);
    }
    
    template <variate_expression lhs_t, const std::size_t var_id> auto operator -(const lhs_t& lhs, const var_t<var_id>& rhs)
    {
        return binary_operation_t<lhs_t, var_t<var_id>, op_difference>(lhs, rhs);
    }
    
    template <variate_expression lhs_t, const std::size_t var_id> auto operator *(const lhs_t& lhs, const var_t<var_id>& rhs)
    {
        return binary_operation_t<lhs_t, var_t<var_id>, op_product>(lhs, rhs);
    }
    
    template <variate_expression lhs_t, const std::size_t var_id> auto operator /(const lhs_t& lhs, const var_t<var_id>& rhs)
    {
        return binary_operation_t<lhs_t, var_t<var_id>, op_quotient>(lhs, rhs);
    }
    
    template <typename lhs_t, const std::size_t var_id>
    requires (!variate_expression<lhs_t>)
    auto operator +(const lhs_t& lhs, const var_t<var_id>& rhs)
    {
        return binary_operation_t<constant_t<lhs_t>, var_t<var_id>, op_sum>(constant_t<lhs_t>(lhs), rhs);
    }
    
    template <typename lhs_t, const std::size_t var_id>
    requires (!variate_expression<lhs_t>)
    auto operator -(const lhs_t& lhs, const var_t<var_id>& rhs)
    {
        return binary_operation_t<constant_t<lhs_t>, var_t<var_id>, op_difference>(constant_t<lhs_t>(lhs), rhs);
    }
    
    template <typename lhs_t, const std::size_t var_id>
    requires (!variate_expression<lhs_t>)
    auto operator *(const lhs_t& lhs, const var_t<var_id>& rhs)
    {
        return binary_operation_t<constant_t<lhs_t>, var_t<var_id>, op_product>(constant_t<lhs_t>(lhs), rhs);
    }
    
    template <typename lhs_t, const std::size_t var_id>
    requires (!variate_expression<lhs_t>)
    auto operator /(const lhs_t& lhs, const var_t<var_id>& rhs)
    {
        return binary_operation_t<constant_t<lhs_t>, var_t<var_id>, op_quotient>(constant_t<lhs_t>(lhs), rhs);
    }
}