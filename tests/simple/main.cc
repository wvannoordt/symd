#include <iostream>
#include "symd.h"

int main(int argc, char** argv)
{
    //define symbols
    enum syms {xv, yv};
    
    //create symbolic variable types
    symd::var_t<xv> x;
    symd::var_t<yv> y;
    
    //define a function
    auto func = x*x + y*y;
    auto result = func(x=1.1, y=2.1);
    
    std::cout << result << std::endl;
    // "5.62"
    
    return 0;
}