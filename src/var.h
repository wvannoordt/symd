#pragma once

#include "var_list.h"

namespace symd
{
    template <const std::size_t var_id> struct var_t
    {
        template <typename rhs_t> auto operator* (const rhs_t& rhs)
        {
            return binary_operation_t<var_t<var_id>, op_product, rhs_t>();
        }
        
        template <typename data_t> auto operator()(const data_t& data)
        {
            return data;
        }
    };
}