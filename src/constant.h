#pragma once

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
    };
}