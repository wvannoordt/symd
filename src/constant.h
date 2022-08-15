#pragma once

#include "sym_type.h"
#include "zero.h"
#include "var_list.h"

namespace symd
{    
    template <typename base_t> struct constant_t
    {
        typedef no_var_t variable_t;
        base_t data;
        constant_t(){}
        constant_t(const base_t& data_in){data = data_in;}
        
        template <typename... assignments_t>
        auto operator()(assignments_t... assignments) const
        {
            return data;
        }
        
        template <typename rhs_t> requires (!variate_expression<rhs_t>)
        auto operator + (const rhs_t& rhs) const
        {
            return constant_t(data+rhs);
        }
        
        template <typename rhs_t> requires (!variate_expression<rhs_t>)
        auto operator - (const rhs_t& rhs) const
        {
            return constant_t(data-rhs);
        }
        
        template <typename rhs_t> requires (!variate_expression<rhs_t>)
        auto operator / (const rhs_t& rhs) const
        {
            return constant_t(data/rhs);
        }
        
        template <typename rhs_t> requires (!variate_expression<rhs_t>)
        auto operator * (const rhs_t& rhs) const
        {
            return constant_t(data*rhs);
        }
        
        template <const symbol_t var_id> zero_t differentiate() const {return zero_t();}
    };
    
    template <typename lhs_t, typename rhs_t> requires (!variate_expression<lhs_t>)
    auto operator + (const lhs_t& lhs, const constant_t<rhs_t>& rhs)
    {
        return constant_t(lhs+rhs.data);
    }
    
    template <typename lhs_t, typename rhs_t> requires (!variate_expression<lhs_t>)
    auto operator - (const lhs_t& lhs, const constant_t<rhs_t>& rhs)
    {
        return constant_t(lhs-rhs.data);
    }
    
    template <typename lhs_t, typename rhs_t> requires (!variate_expression<lhs_t>)
    auto operator * (const lhs_t& lhs, const constant_t<rhs_t>& rhs)
    {
        return constant_t(lhs*rhs.data);
    }
    
    template <typename lhs_t, typename rhs_t> requires (!variate_expression<lhs_t>)
    auto operator / (const lhs_t& lhs, const constant_t<rhs_t>& rhs)
    {
        return constant_t(lhs/rhs.data);
    }
}