#pragma once

#include "assignment.h"

namespace symd
{
    
    template <typename assign_t>
    auto create_assignment_list_recursive(const assign_t& assignment)
    {
        return 0.0;
    }
    
    template <typename assign_t, typename... assignments_t>
    auto create_assignment_list_recursive(const assign_t& assignment, assignments_t... assignments)
    {
        return 0.0;
    }
    
    template <typename... assignments_t> auto create_assignment_list(assignments_t... assignments)
    {
        return create_assignment_list_recursive(assignments...);
    }
}