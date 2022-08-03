#include <print.h>
#include "symd.h"

int main(int argc, char** argv)
{
    enum syms2 {x, y, z};
    
    symd::var_t<x> x_v;
    symd::var_t<y> y_v;
    symd::var_t<z> z_v;
    
    auto func   = x_v*y_v;
    
    auto vl = symd::make_var_list_t<x, y>::type();
    auto vr = symd::make_var_list_t<x, y, z>::type();
    auto vu = symd::var_list_union<symd::make_var_list_t<x, y>::type, symd::make_var_list_t<x, y, x, x, x, x, z>::type>::type();
    auto vq = symd::var_list_unique<symd::make_var_list_t<x, y, x, y, x, y, z, y, x>::type>::type();
    print(vq.size());
    
    // auto val1   = func(x_v=1.0, y_v=2.0);
    // auto vec1_v = symd::vector(x_v, y_v);
    // auto vec2_v = symd::vector(x_v, y_v, z_v);
    // auto val2   = func(vec1_v={1.0, 2.0});
    // auto val2   = func(vec2_v={1.0, 2.0,3.0}); // ignores the 3.0
    // auto val3   = func(x_v=1.0); // compile-time error
    
    // wishlist
    
    // enum syms1 {rho_l, rho_r, u_l, u_r, p_l, p_r};
    // 
    // symd::var_t<rho_l> rho_l_v;
    // symd::var_t<rho_r> rho_r_v;
    // symd::var_t<u_l> u_l_v;
    // symd::var_t<u_r> u_r_v;
    // symd::var_t<p_l> p_l_v;
    // symd::var_t<p_r> p_r_v;
    // auto sym_vec   = symd::vector(rho_l_v, rho_r_v, u_l_v, u_r_v, p_l_v, p_r_v);
    // auto flux_func = symd::vector_func(0.25*(rho_l_v+rho_r_v)*(u_l_v+u_r_v), 0.125*(rho_l_v+rho_r_v)*(u_l_v+u_r_v)*(u_l_v+u_r_v)+0.5*(p_l_v + p_r_v));
    // auto jacobian  = symd::ddx<sym_vec>(flux_func);
    // auto var_list = symd::var_list_union<symd::make_var_list_t<x>::type, symd::make_var_list_t<x, y>::type>::type();
    return 0;
}