# SYMD (Symbolic Differentiation)

SYMD is a static symbolic differentiation library. The primary difference between SYMD and
other symbolic calculus implementations in c++ is that SYMD represents functions through
types, making them zero-overhead at runtime. This allows for the use of SYMD in
high-performance applications where analytical differentiation is required (mainly
inspired by scientific simulation codes).

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
    
    //define a composite function
    auto comp = func(y=x*x);
    result = comp(x=2.0);
    std::cout << result << std::endl;
    // "56"
    
    return 0;
}
```