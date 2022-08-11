#pragma once

#include "var_list.h"
#include "bin_ops.h"

namespace symd
{
    //START HERE
    struct unity_t
    {
        typedef no_var_t variable_t;
        template <typename rhs_t> auto operator+(const rhs_t& rhs) {return rhs;}
        template <typename rhs_t> auto operator-(const rhs_t& rhs) {return rhs;}
        template <typename rhs_t> auto operator/(const rhs_t& rhs) {return unity_t();}
        template <typename rhs_t> auto operator*(const rhs_t& rhs) {return unity_t();}
    };
    
    template <typename lhs_t> auto operator+(const lhs_t& lhs, const unity_t& zero) {return lhs;}
    template <typename lhs_t> auto operator-(const lhs_t& lhs, const unity_t& zero) {return lhs;}
    template <typename lhs_t> auto operator/(const lhs_t& lhs, const unity_t& zero) {return undefined_t();}
    template <typename lhs_t> auto operator*(const lhs_t& lhs, const unity_t& zero) {return unity_t();}
}