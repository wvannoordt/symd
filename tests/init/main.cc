#include <print.h>
#include "symd.h"

int main(int argc, char** argv)
{
    enum syms {x, y, z};
    symd::var_t<x> xv;
    symd::var_t<y> yv;
    auto x2 = xv*yv;
    
    auto var_list = symd::var_list_union<symd::make_var_list_t<x>::type, symd::make_var_list_t<x, y>::type>::type();
    return 0;
}