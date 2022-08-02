#pragma once

#include <type_traits>

#include "sym_type.h"

namespace symd
{    
    struct no_var_t
    {
        static std::size_t size(void) {return 0;}
    };
    template <const symbol_t val, typename next_t> struct var_list_t
    {
        static std::size_t size(void) {return 1+next_t::size();};
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
    template <typename lhs_t, typename rhs_t> struct var_list_union
    {
        typedef int type;//begin here!
    };
}