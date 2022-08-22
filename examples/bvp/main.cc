#include "symd.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

//Some implementation details are hidden in the following header, but
//are not necessary for understanding this example.
#include "./tdma.h"

int main(int argc, char** argv)
{
	const std::size_t n = 800;
	example::tridiag_t lhs(n, 0.0);
	lhs.set_diag(-1,  1.0);
	lhs.set_diag( 0, -2.0);
	lhs.set_diag( 1,  1.0);
	std::vector rhs(n, 1.0/(n*n));
	auto sol = example::tdma_solve_inplace(lhs, rhs);
	std::ofstream myfile("out.csv");
	for (const auto y: sol) myfile << y << "\n";
	return 0;
}