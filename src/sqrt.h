#pragma once

#include "constant.h"
#include "unary.h"
#include "forward_expression.h"

namespace symd
{
    template <typename T> concept sqrt_evaluatable = requires (T t) {std::sqrt(t);};
    template <typename expression_t> struct sqrt_t : public unary_operation_t<expression_t, sqrt_t<expression_t>>
    {
        typedef unary_operation_t<expression_t, sqrt_t<expression_t>> base_t;
        using base_t::base_t;
        
        template <const symbol_t var_id> 
        requires (var_list_contains<typename base_t::variable_t, var_id>::value)
        auto differentiate(void) const
        {
            return (this->expression. template differentiate<var_id>())/(2*sqrt_t<expression_t>(this->expression));
        }
        
        template <sqrt_evaluatable data_t>
        static auto eval_sqrt(const data_t& data)
        {
            return std::sqrt(data);
        }
        
        template <typename data_t>
        requires (!sqrt_evaluatable<data_t>)
        static auto eval_sqrt(const data_t& data)
        {
            return sqrt_t<data_t>(data);
        }
        
        template <typename... assignments_t> auto operator()(assignments_t... assignments) const
        {
            return eval_sqrt((this->expression)(assignments...));
        }
    };
    
    template <typename expression_t>
    auto sqrt(const expression_t& expression)
    {
        typedef typename forward_expression_t<expression_t>::type base_expression_t;
        return sqrt_t<base_expression_t>(forward_expression(expression));
    }
}