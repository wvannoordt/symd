#pragma once

#include "sym_type.h"

namespace symd
{
    //to be refined later
    template <typename T> concept assignable_numeric_type     = std::is_arithmetic<T>::value;
    template <typename T> concept assignable_expression_type  = variate_expression<T>;
    template <typename T> concept valid_assignment_type       = assignable_numeric_type<T> || assignable_expression_type<T>;
    
    
    template <const symbol_t var_id, typename assigned_t> struct assignment_t
    {
        constexpr static symbol_t assigned_var() {return var_id;}
        assigned_t value;
        assignment_t(const assigned_t& value_in) { value = value_in; }
        assignment_t() {}
    };
    
    template <const symbol_t var_id> 
    constexpr bool contains_assignment_for()
    {
        return false;
    }
    
    template <const symbol_t var_id, typename assignment_t, typename... assignments_t> 
    constexpr bool contains_assignment_for()
    {
        return (assignment_t::assigned_var()==var_id)||contains_assignment_for<var_id, assignments_t...>();
    }
    
    template <const symbol_t var_id, typename assignment_t>
    auto fetch_assignment_value(const assignment_t& assignment)
    {
        return assignment.value;
    }
    
    template <const symbol_t var_id, typename assignment_t, typename... assignments_t>
    requires (var_id == assignment_t::assigned_var())
    auto fetch_assignment_value(const assignment_t& assignment, const assignments_t&... assignments)
    {
        return assignment.value;
    }
    
    template <const symbol_t var_id, typename assignment_t, typename... assignments_t>
    requires (var_id != assignment_t::assigned_var())
    auto fetch_assignment_value(const assignment_t& assignment, const assignments_t&... assignments)
    {
        return fetch_assignment_value<var_id, assignments_t...>(assignments...);
    }
}