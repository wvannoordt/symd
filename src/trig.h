#pragma once

#include "unary.h"
#include "forward_expression.h"

namespace symd
{
    enum trig_function
    {
        trig_sin,
        trig_cos,
        trig_tan,
        trig_sec,
        trig_csc,
        trig_cot
    };
    
    template <typename T> concept trig_evaluatable = requires (T t)
    {
        std::sin(t);
        std::cos(t);
        std::tan(t);
    };
    
    template <typename expression_t, const trig_function tfunc>
    struct trig_t : public unary_operation_t<expression_t, trig_t<expression_t, tfunc>>
    {
        typedef unary_operation_t<expression_t, trig_t<expression_t, tfunc>> base_t;
        using base_t::base_t;
        
        template <const symbol_t var_id> 
        requires (!var_list_contains<typename base_t::variable_t, var_id>::value)
        zero_t differentiate(void) const
        {
            return zero_t();
        }
        
        template <const symbol_t var_id>
        requires (var_list_contains<typename base_t::variable_t, var_id>::value && (tfunc==trig_sin))
        auto differentiate(void) const
        {
            return trig_t<expression_t, trig_cos>(this->expression) * this->expression. template differentiate<var_id>();
        }
        
        template <const symbol_t var_id>
        requires (var_list_contains<typename base_t::variable_t, var_id>::value && (tfunc==trig_cos))
        auto differentiate(void) const
        {
            return -1*trig_t<expression_t, trig_sin>(this->expression) * this->expression. template differentiate<var_id>();
        }
        
        template <const symbol_t var_id>
        requires (var_list_contains<typename base_t::variable_t, var_id>::value && (tfunc==trig_tan))
        auto differentiate(void) const
        {
            return (
                trig_t<expression_t, trig_sec>(this->expression)*
                trig_t<expression_t, trig_sec>(this->expression)
            ) * this->expression. template differentiate<var_id>();
        }
        
        template <const symbol_t var_id>
        requires (var_list_contains<typename base_t::variable_t, var_id>::value && (tfunc==trig_sec))
        auto differentiate(void) const
        {
            return (
                trig_t<expression_t, trig_tan>(this->expression)*
                trig_t<expression_t, trig_sec>(this->expression)
            ) * this->expression. template differentiate<var_id>();
        }
        
        template <const symbol_t var_id>
        requires (var_list_contains<typename base_t::variable_t, var_id>::value && (tfunc==trig_csc))
        auto differentiate(void) const
        {
            return (-1*
                trig_t<expression_t, trig_csc>(this->expression)*
                trig_t<expression_t, trig_cot>(this->expression)
            ) * this->expression. template differentiate<var_id>();
        }
        
        template <const symbol_t var_id>
        requires (var_list_contains<typename base_t::variable_t, var_id>::value && (tfunc==trig_cot))
        auto differentiate(void) const
        {
            return (-1*
                trig_t<expression_t, trig_csc>(this->expression)*
                trig_t<expression_t, trig_csc>(this->expression)
            ) * this->expression. template differentiate<var_id>();
        }
        
        template <trig_evaluatable data_t> requires (tfunc == trig_sin)
        static auto eval_trig(const data_t& data) { return std::sin(data); }
        
        template <trig_evaluatable data_t> requires (tfunc == trig_cos)
        static auto eval_trig(const data_t& data) { return std::cos(data); }
        
        template <trig_evaluatable data_t> requires (tfunc == trig_tan)
        static auto eval_trig(const data_t& data) { return std::tan(data); }
        
        template <trig_evaluatable data_t> requires (tfunc == trig_csc)
        static auto eval_trig(const data_t& data) { return 1/std::sin(data); }
        
        template <trig_evaluatable data_t> requires (tfunc == trig_sec)
        static auto eval_trig(const data_t& data) { return 1/std::cos(data); }
        
        template <trig_evaluatable data_t> requires (tfunc == trig_cot)
        static auto eval_trig(const data_t& data) { return 1/std::tan(data); }
        
        template <typename data_t> requires (!trig_evaluatable<data_t>)
        static auto eval_trig(const data_t& data) { return trig_t<data_t, tfunc>(data); }
        
        template <typename... assignments_t> auto operator()(assignments_t... assignments) const
        {
            return eval_trig((this->expression)(assignments...));
        }
    };
    
    template <typename expression_t, const trig_function tfunc>
    auto make_trig(const expression_t& expression)
    {
        typedef typename forward_expression_t<expression_t>::type base_expression_t;
        return trig_t<base_expression_t, tfunc>(forward_expression(expression));
    }
    
    template <typename expression_t> auto sin(const expression_t& expression) {return make_trig<expression_t,trig_sin>(expression);}
    template <typename expression_t> auto cos(const expression_t& expression) {return make_trig<expression_t,trig_cos>(expression);}
    template <typename expression_t> auto tan(const expression_t& expression) {return make_trig<expression_t,trig_tan>(expression);}
    template <typename expression_t> auto sec(const expression_t& expression) {return make_trig<expression_t,trig_sec>(expression);}
    template <typename expression_t> auto csc(const expression_t& expression) {return make_trig<expression_t,trig_csc>(expression);}
    template <typename expression_t> auto cot(const expression_t& expression) {return make_trig<expression_t,trig_cot>(expression);}
}