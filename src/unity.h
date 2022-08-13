#pragma once

#include "var_list.h"
#include "bin_ops.h"

namespace symd
{
    struct unity_t
    {
        typedef no_var_t variable_t;
        template <typename rhs_t> auto operator+(const rhs_t& rhs) {return binary_operation_t<unity_t, rhs_t, op_sum>(unity_t(), rhs);}
        template <typename rhs_t> auto operator-(const rhs_t& rhs) {return binary_operation_t<unity_t, rhs_t, op_difference>(unity_t(), rhs);}
        template <typename rhs_t> auto operator/(const rhs_t& rhs) {return 1/rhs;}
        template <typename rhs_t> auto operator*(const rhs_t& rhs) {return rhs;}
    };
    
    template <typename lhs_t> auto operator+(const lhs_t& lhs, const unity_t& uni) {return binary_operation_t<lhs_t, unity_t, op_sum>(lhs, unity_t());}
    template <typename lhs_t> auto operator-(const lhs_t& lhs, const unity_t& uni) {return binary_operation_t<lhs_t, unity_t, op_difference>(lhs, unity_t());}
    template <typename lhs_t> auto operator/(const lhs_t& lhs, const unity_t& uni) {return lhs;}
    template <typename lhs_t> auto operator*(const lhs_t& lhs, const unity_t& uni) {return lhs;}
}