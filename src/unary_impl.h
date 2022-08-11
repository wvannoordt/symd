#pragma once

#include "constant.h"
#include "unary.h"
#include "forward_expression.h"

namespace symd
{
    template <typename expression_t> struct exp_t : public unary_operation_t<expression_t, exp_t<expression_t>>
    {
        typedef unary_operation_t<expression_t, exp_t<expression_t>> base_t;
        using base_t::base_t;
        
        template <const symbol_t var_id> 
        requires (!var_list_contains<typename base_t::variable_t, var_id>::value)
        zero_t differentiate(void) const
        {
            return zero_t();
        }
        
        template <const symbol_t var_id> 
        requires (var_list_contains<typename base_t::variable_t, var_id>::value)
        auto differentiate(void) const
        {
            return exp_t<expression_t>(this->expression)*this->expression. template differentiate<var_id>();
        }
    };
    
    template <typename expression_t>
    auto exp(const expression_t& expression)
    {
        typedef typename forward_expression_t<expression_t>::type base_expression_t;
        return exp_t<base_expression_t>(forward_expression(expression));
    }
}