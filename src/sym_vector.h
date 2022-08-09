#pragma once

#include <concepts>
#include "var_list.h"

namespace symd
{
    
    template <typename T> concept sym_vector_type = requires(T t)
    {
        T::size();
        t.next;
        t.val;
    };
    
    template <typename T> concept basic_symbol_vector_type = sym_vector_type<T> && requires(T t)
    {
        
    }
    
    template <typename val_t, typename next_t> struct vector_t
    {
        val_t val;
        next_t next;
        constexpr static std::size_t size(void) {return 1 + next_t::size();};
        vector_t(void){}
        vector_t(const val_t& val_in, const next_t& next_in)
        {
            val = val_in;
            next = next_in;
        }
    };
    
    template <typename val_t> auto create_vector(const val_t& val)
    {
        return vector_t(val, no_var_t());
    }
    
    template <typename val_t, typename... vals_t> auto create_vector(const val_t& val, vals_t... vals)
    {
        return vector_t(val, create_vector(vals...));
    }
    
    template <typename... params_t> auto vector(params_t... params)
    {
        return create_vector(params...);
    }
}