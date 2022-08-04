#pragma once

#include "var_list.h"

namespace symd
{
    //CRTP
    template <typename expression_t, typename derived_t> struct unary_operation_t
    {
        expression_t expression;
        unary_operation_t(){}
        unary_operation_t(const expression_t& expression_in){expression = expression_in;}
    };
}