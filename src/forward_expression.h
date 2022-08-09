#pragma once

#include "var_list.h"
#include "constant.h"

namespace symd
{
    template <typename expression_t> struct forward_expression_t
    {
        typedef typename std::conditional
        <
            variate_expression<expression_t>,
            expression_t,
            constant_t<expression_t>
        >::type type;
    };
    
    template <variate_expression expression_t>
    expression_t forward_expression(const expression_t& expr) { return expr; }
    
    template <typename expression_t>
    requires (!variate_expression<expression_t>)
    constant_t<expression_t> forward_expression(const expression_t& expr)
    { return constant_t<expression_t>(expr); }
}