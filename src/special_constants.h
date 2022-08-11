#pragma once

#include "var_list.h"

namespace symd
{
    struct undefined_t
    {
        typedef no_var_t variable_t;
    };
    
    struct zero_t
    {
        typedef no_var_t variable_t;
        template <typename rhs_t> auto operator+(const rhs_t& rhs) {return rhs;}
        template <typename rhs_t> auto operator-(const rhs_t& rhs) {return rhs;}
        template <typename rhs_t> auto operator/(const rhs_t& rhs) {return zero_t();}
        template <typename rhs_t> auto operator*(const rhs_t& rhs) {return zero_t();}
    };
    
    template <typename lhs_t> auto operator+(const lhs_t& lhs, const zero_t& zero) {return lhs;}
    template <typename lhs_t> auto operator-(const lhs_t& lhs, const zero_t& zero) {return lhs;}
    template <typename lhs_t> auto operator/(const lhs_t& lhs, const zero_t& zero) {return undefined_t();}
    template <typename lhs_t> auto operator*(const lhs_t& lhs, const zero_t& zero) {return zero_t();}
    
    // struct unity_t
    // {
    //     typedef no_var_t variable_t;
    //     template <typename rhs_t> auto operator+(const rhs_t& rhs) {return rhs;}
    //     template <typename rhs_t> auto operator-(const rhs_t& rhs) {return rhs;}
    //     template <typename rhs_t> auto operator/(const rhs_t& rhs) {return unity_t();}
    //     template <typename rhs_t> auto operator*(const rhs_t& rhs) {return unity_t();}
    // };
    // 
    // template <typename lhs_t> auto operator+(const lhs_t& lhs, const unity_t& zero) {return lhs;}
    // template <typename lhs_t> auto operator-(const lhs_t& lhs, const unity_t& zero) {return lhs;}
    // template <typename lhs_t> auto operator/(const lhs_t& lhs, const unity_t& zero) {return undefined_t();}
    // template <typename lhs_t> auto operator*(const lhs_t& lhs, const unity_t& zero) {return unity_t();}
}