#include <iostream>
#include "symd.h"

int main(int argc, char** argv)
{
    //define symbols
    enum syms {xv, yv};
    
    //create symbolic variable types
    symd::var_t<xv> x;
    symd::var_t<yv> y;
    
    //define/evaluate a function
    auto func = y*y + x*x;
    auto result = func(x=1.1, y=2.1);
    
    std::cout << result << std::endl;
    // "5.62"
    
    //differentiate the function with respect to variable "x"
    auto func_diff = symd::ddx(func, x);
    result = func_diff(x=1.1, y=2.1);
    
    std::cout << result << std::endl;
    // "2.2"


    //=================================
    

    auto func = y*y;
    ++func;

    return 0;
}