#include <concepts>
#include <print.h>
#include "symd.h"

int main(int argc, char** argv)
{
    enum syms2 {x, y, z, p, q};
    
    symd::var_t<x> x_v;
    symd::var_t<y> y_v;
    symd::var_t<z> z_v;
    symd::var_t<p> p_v;
    symd::var_t<q> q_v;
    
    auto f0   = x_v*y_v;
    auto f1   = f0 + x_v*z_v;
    // auto f_x = symd::ddx<x_v>();
    
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
    
    
    //"dream" use case (example: solving a nonlinear system)
    // enum vars   {ul, uc, ur, x};
    // enum params {delta_x};
    // 
    // 
    // symd::var_t<ul> ul_v;
    // symd::var_t<uc> uc_v;
    // symd::var_t<ur> ur_v;
    // symd::var_t<x>  x_v;
    // 
    // 
    // symd::param_t<delta_x> dx_p;
    // 
    // dx_p=2.5e-3;
    // 
    // auto nl  = u_c*(ul_v-ur_v)/(2*dx_p);
    // auto rhs = (ul_v - 2*uc_v + ur_v)/(dx_p*dx_p) + nl*nl;
    // 
    // auto rhs_val = rhs(ul_v=1.0, uc_v=2.0, ur_v=3.0); //-> gives back a double or something
    // auto vec = symd::var_vector(ul_v, uc_v, ur_v);
    // 
    // auto rhs_jac = symd::ddx<vec>(rhs);
    // auto jac_val = rhs_jac(ul_v=1.0, uc_v=2.0, ur_v=3.0); //-> gives back an array
    // 
    // auto u0 = 2*x_v;
    // //etc etc
    
    return 0;
}