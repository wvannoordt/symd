#pragma once
#include "unity.h"
#include "zero.h"

namespace symd
{
    constexpr static auto one() {return unity_t();}
    constexpr static auto zero() {return zero_t();}
}