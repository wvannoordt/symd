# SYMD (Symbolic Differentiation)

SYMD is a static symbolic differentiation library. The primary difference between SYMD and
other symbolic calculus implementations in c++ is that SYMD represents functions through
types, making them zero-overhead at runtime. This allows for the use of SYMD in
high-performance applications where analytical differentiation is required (mainly
inspired by scientific simulation codes).

## Building and Installation

SYMD is a header-only implementation -- it can be included in a project through the
single header file `src/symd.h`. All of the public utilities in SYMD fall under the
`symd` namespace.

## Simple Example

hello
