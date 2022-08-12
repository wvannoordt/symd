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

## Example

The following example simply defines a function and evaluates it. Note that
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
    
    //define a function
    auto func = x*x + y*y;
    auto result = func(x=1.1, y=2.1);
    
    std::cout << result << std::endl;
    // "5.62"
    
    return 0;
}
```