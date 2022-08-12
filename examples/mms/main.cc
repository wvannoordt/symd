#include <iostream>
#include "symd.h"

double mms1()
{
    return 0.0;
}

int main(int argc, char** argv)
{
    //This test performs the method of manufactured solutions (MMS)
    //on a 2-D implementation of the laplacian operator (d^2/dx^2 + d^2/dy^2)
    enum syms {xv, yv};
    symd::var_t<xv> x;
    symd::var_t<yv> y;
    
    auto func = x*x + y*y;
    auto rhs  = symd::ddx<3>(func*func, x);
    
    return 0;
}