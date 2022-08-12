#pragma once

#include <type_traits>
#include <concepts>

#include "sym_type.h"

namespace symd
{
    template <typename T> concept variate_expression = requires(T t)
    {
        T::variable_t::size();
    };
    
    struct no_var_t
    {
        constexpr static std::size_t size(void) {return 0;}
    };
    template <const symbol_t elem, typename next_t> struct var_list_t
    {
        constexpr static std::size_t size(void) {return 1+next_t::size();};
        constexpr static symbol_t val(void) {return elem;}
        typedef next_t next_type;
    };
    template <const symbol_t... vals> struct varlist_dummy;
    template <const symbol_t val, const symbol_t... vals> struct varlist_dummy<val, vals...>;
    template <const symbol_t... vals> struct make_var_list_t
    {
        typedef std::conditional<sizeof...(vals)==0, no_var_t, typename varlist_dummy<vals...>::type>::type type;
    };
    template <const symbol_t... vals> struct varlist_dummy
    {
        typedef no_var_t type;
    };
    template <const symbol_t val, const symbol_t... vals> struct varlist_dummy<val, vals...>
    {
        typedef var_list_t<val, typename make_var_list_t<vals...>::type> type;
    };
    template <typename lhs_t, typename rhs_t> struct var_list_concat_helper
    {
        typedef var_list_t
        <
            lhs_t::val(),
            typename std::conditional
            <
                lhs_t::next_type::size()==0,
                rhs_t,
                typename var_list_concat_helper
                <
                    typename lhs_t::next_type,
                    rhs_t
                >::type
            >::type
        > type;
    };
    
    template <> struct var_list_concat_helper<no_var_t, no_var_t>
    {
        typedef no_var_t type;
    };
    
    template <typename rhs_t> struct var_list_concat_helper<no_var_t, rhs_t>
    {
        typedef rhs_t type;
    };
    template <typename lhs_t> struct var_list_concat_helper<lhs_t, no_var_t>
    {
        typedef lhs_t type;
    };
    
    template <typename lhs_t, typename rhs_t> struct var_list_concat
    {
        typedef typename std::conditional
        <
            lhs_t::size()==0,
            rhs_t,
            typename std::conditional
            <
                rhs_t::size()==0,
                lhs_t,
                typename var_list_concat_helper<lhs_t,rhs_t>::type
            >::type
        >::type type;
    };
    
    template <typename list_t, const symbol_t var_id> struct var_list_contains
    {
        const static bool value = var_id==list_t::val() || var_list_contains<typename list_t::next_type, var_id>::value;
    };
    
    template <const symbol_t var_id> struct var_list_contains<no_var_t, var_id>
    {
        const static bool value = false;
    };
    
    template <typename list_t, typename accum_t> struct var_list_unique_helper
    {
        typedef typename std::conditional
        <
            list_t::size()==0,
            accum_t,
            typename std::conditional
            <
                var_list_contains<accum_t,list_t::val()>::value,
                typename var_list_unique_helper<typename list_t::next_type, accum_t>::type,
                typename var_list_unique_helper<typename list_t::next_type, var_list_t<list_t::val(),accum_t>>::type
            >::type
        >::type type;
    };
    
    template <typename accum_t> struct var_list_unique_helper<no_var_t, accum_t>
    {
        typedef accum_t type;
    };
    
    template <typename list_t> struct var_list_unique
    {
        typedef typename var_list_unique_helper<list_t, no_var_t>::type type;
    };
    
    template <typename lhs_t, typename rhs_t> struct var_list_union
    {
        typedef typename var_list_unique<typename var_list_concat<lhs_t, rhs_t>::type>::type type;
    };
}