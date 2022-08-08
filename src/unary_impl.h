#pragma once

#include "constant.h"
#include "unary.h"

namespace symd
{
    template <typename expression_t> struct exp_t : public unary_operation_t<expression_t, exp_t<expression_t>>
    {
        typedef unary_operation_t<expression_t, exp_t<expression_t>> base_t;
        
        using base_t::base_t;
    };
    
    template <variate_expression expression_t>
    auto exp(const expression_t& expression)
    {
        return exp_t<expression_t>(expression);
    }
    
    template <typename expression_t>
    requires(!variate_expression<expression_t>)
    auto exp(const expression_t& expression)
    {
        return exp_t<constant_t<expression_t>>(constant_t<expression_t>(expression));
    }
}