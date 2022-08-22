# SYMD (Symbolic Differentiation)

SYMD is a static symbolic differentiation library. The primary difference between SYMD and
other symbolic calculus implementations in c++ is that SYMD represents functions through
types, making them zero-overhead at runtime. This allows for the use of SYMD in
high-performance applications where analytical differentiation is required (mainly
inspired by scientific simulation codes). The ideal use of SYMD is to evaluate derivatives
rather than symbolically calculate them for future implementation.

## Building and Installation

SYMD is a header-only implementation -- it can be included in a project through the
single header file `src/symd.h`. All of the public utilities in SYMD fall under the
`symd` namespace. SYMD utilizes concepts from the c++20 standard, so it is recommended
to use e.g. `g++ -std=c++20 ...` to build projects.

## Example -- Basic Usage

The following example simply defines and differentiates
a function and evaluates it. Note that
the assignment-style evaluation syntax `func(x=1.1, y=2.1)` is necessary.

```c++
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
    
    return 0;
}
```

## Example -- Partial Evaluation

SYMD also supports the partial evaluation of functions to define other functions.
For example, the function `f(x,y) = 3*y*y + x*x*x` can be partially evaluated by
setting `y=2` to give `g(x) = f(x,2) = 12+x*x*x`. The resulting partially-evaluated
function can be differentiated as well.

Additionally, the partial evaluation need not constrain the evaluation to a constant:
we can define `h(x) = f(x,x*x) = 3*x*x*x*x+x*x*x` to get another function.
All of this is illustrated in the following example:

```c++
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
    
    //define/evaluate a composite function
    auto comp = func(y=x*x);
    result = comp(x=2.0);
    std::cout << result << std::endl;
    // "56"
    
    return 0;
}
```

## Example -- Automatic Differentiation for Boundary Value Problem

This usage example showcases one of the main utilities of SYMD. Boundary value
problems (BVPs) often arise in scientific computing applications, which solve
a system of equations given as `D(u) = f`. When the operator `D` is nonlinear,
this must be done iteratively, requiring the computation of the matrix
`d(D(u)-f)/du`. Depending on the operator, this can result in a large number of
implementations that require maintenance.

SYMD provides a way to automatically maintain these implementations. For example,
we might compute the three-point stencil for `(d^2/dx^d + (d/dx)^2)` as

```c++
    
    enum syms {ul_v, uc_v, ur_v, x_v};
    symd::var_t<ul_v> ul;
    symd::var_t<uc_v> uc;
    symd::var_t<ur_v> ur;
    symd::var_t<x_v>  x;
    auto deriv    = (ur-ul)*r1;
    auto deriv2   = (ul-2.0*uc+ur)*r2;
    auto rhs_func = deriv2 + deriv*deriv
```

In order to solve a system like `(d^2/dx^d + (d/dx)^2)(u) = f`, we need to evaluate
the derivatives of `rhs_func` with respect to `ul`, `uc`, and `ur`. With SYMD, we
need not implement these manually, but can rather just evaluate the derivatives exactly:

```c++
    rhs[j]    = rhs_func(ul=u[j], uc=u[j+1], ur=u[j+2], x=x_loc);
    lhs(j,-1) = symd::ddx(rhs_func, ul)(ul=u[j], uc=u[j+1], ur=u[j+2], x=x_loc);
    lhs(j, 0) = symd::ddx(rhs_func, uc)(ul=u[j], uc=u[j+1], ur=u[j+2], x=x_loc);
    lhs(j, 1) = symd::ddx(rhs_func, ur)(ul=u[j], uc=u[j+1], ur=u[j+2], x=x_loc);
```

For the full implementation, the reader is referred to `examples/bvp`.

## Other Features

Other features not listed above are available in SYMD, including:

* Higher-order derivatives:

`auto d2f_dx2 = symd::ddx<2>(f, x)`

* Standard mathematical functions: `sqrt`, `exp`, `sin`, `cos`, `tan`, `csc`, `sec`, etc.

For more information, the reader is referred to the `examples` directory.