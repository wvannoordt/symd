#include <print.h>
#include "symd.h"

int main(int argc, char** argv)
{
    enum syms {x_v, y_v, z_v, w_v, t_v};
    
    symd::var_t<x_v> x;
    symd::var_t<y_v> y;
    symd::var_t<z_v> z;
    symd::var_t<w_v> w;
    symd::var_t<t_v> t;
    
    auto f0 = x_v+y;
    auto h0 = f0 + w;
    auto f1 = 13*((x*z + f0)*w + 5);
    auto f2 = f1*h0;
    auto f3 = symd::exp(f0) + x;
    auto f4 = 1 + symd::exp(f0) + 15*y+f2 + symd::exp(y);
    // 
    // auto vec1 = symd::vector(x, y, z); // -> unique, variable-only vector
    // auto vec2 = symd::vector(x, y, z*y); // -> unique, non variable-only vector
    // auto vec3 = symd::vector(x, y, z*y, x); // -> non unique, non variable-only vector
    // auto vec4 = symd::vector(x, y, x); // -> non unique, variable-only vector
    // 
    auto f4_jac = symd::ddx(symd::exp(y), x);
    auto expf = symd::exp(x*x);
    auto dx = symd::ddx<2>(symd::sqrt(x), x);

    std::cout << dx(x=4.0) << std::endl;
    // print(diff(x=1.0));
    
    //idea: the vector function retues a pure unique variable-only vector when it can
    //otherwise, it returns a basic vector type. Therefore, only vec1 is a valid vector
    //to differentiate against. We should also be able to build a symbolic vector from a
    //var_list
    
    // print(symd::sym_vector_type<decltype(vec1)>);
    // print(symd::sym_vector_type<decltype(vec2)>);
    // print(symd::sym_vector_type<decltype(vec3)>);
    // print(symd::sym_vector_type<decltype(vec4)>);
    // print(sizeof(decltype(vec1)));
    // print(sizeof(decltype(vec2)));
    // print(sizeof(decltype(vec3)));
    // print(sizeof(decltype(vec4)));
    
    
    
    // auto val = f0(x=1.0, y=2.0);
    // ++f4;
    // ++f3;
    // auto f_x = symd::ddx<x>()
    
    // another idea: partial evaluation:
    // auto h1 = x + y*y;
    // auto h2 = h1(y=2.0); //-> equivalent to x + 4.0
    
    // auto val1   = func(x=1.0, y=2.0);
    // auto vec1_v = symd::vector(x, y);
    // auto vec2_v = symd::vector(x, y, z);
    // auto val2   = func(vec1={1.0, 2.0});
    // auto val2   = func(vec2={1.0, 2.0,3.0}); // ignores the 3.0
    // auto val3   = func(x=1.0); // compile-time error
    
    // wishlist
    
    // enum syms1 {rho_l, rho_r, u_l, u_r, p_l, p_r};
    // 
    // symd::var_t<rho_l> rho_l;
    // symd::var_t<rho_r> rho_r;
    // symd::var_t<u_l> u_l;
    // symd::var_t<u_r> u_r;
    // symd::var_t<p_l> p_l;
    // symd::var_t<p_r> p_r;
    // 
    // auto symec   = symd::vector(rho_l, rho_r, u_l, u_r, p_l, p_r);
    // auto flux_func = symd::vector(0.25*(rho_l+rho_r)*(u_l+u_r), 0.125*(rho_l+rho_r)*(u_l+u_r)*(u_l+u_r)+0.5*(p_l + p_r));
    // auto jacobian  = symd::ddx(flux_func, sym_vec);
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