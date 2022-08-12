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
    auto func = 3*y*y + x*x*x;
    auto part = func(y=2);
    
    auto result = part(x=2.0);
    std::cout << result << std::endl;
    // "20"
    
    //differentiate partially evaluated function
    result = ddx(part, x)(x=2.0);
    std::cout << result << std::endl;
    // "12"
    
    //define a composite function
    auto comp = func(y=x*x);
    result = comp(x=2.0);
    std::cout << result << std::endl;
    // "56"
    
    return 0;
}