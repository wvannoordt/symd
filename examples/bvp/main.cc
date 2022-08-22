#include "symd.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

//Some implementation details are hidden in the following header, but
//are not necessary for understanding this example.
#include "./tdma.h"

typedef double real_t;

int main(int argc, char** argv)
{
	const std::size_t n = 10000000;
	example::tridiag_t lhs(n, 0.0);
	std::vector rhs(n, 0.0);
	
	const real_t pi = 3.14159265359;
	
	const real_t x0 = 0.0;
	const real_t x1 = 2*pi;
	const real_t dx = (x1-x0)/(n+1); // discretize interior only
	
	
	//Here we solve:
	//d^2u/dx^2 + (du/dx)^2 = cos^2 x - sin x, x in (0,2*pi)
	// u(0)  = u(2*pi) = 0
	//the analytical solution is u = sin(x)
	
	//boundary conditions
	const real_t u0 = 0.0;
	const real_t un = 0.0;
	
	enum syms {ul_v, uc_v, ur_v, x_v};
	symd::var_t<ul_v> ul;
	symd::var_t<uc_v> uc;
	symd::var_t<ur_v> ur;
	symd::var_t<x_v>  x;
	
	auto r1 = 1.0/(2*dx);
	auto r2 = 1.0/(dx*dx);
	auto deriv    = (ur-ul)*r1;
	auto deriv2   = (ul-2.0*uc+ur)*r2;
	auto forc     = symd::cos(x)*symd::cos(x) - symd::sin(x);
	
	//This is now a function of (ul, uc, ur, and x)
	auto rhs_func = deriv2 + deriv*deriv - forc;
	
	const real_t tolerance = 1e-6;
	real_t err = tolerance*1000;
	const int max_iterations = 100;
	int iterations = 0;
	auto abs = [](const real_t& a) -> real_t {return a<0.0?-a:a;};
	
	//initial guess: u = 0
	std::vector u(n+2, 0.0);
	u[0]   = u0;
	u[n+1] = un;
	
	while ((abs(err)>tolerance) && (iterations++ < max_iterations))
	{
		for (int j = 0; j < n; ++j)
		{
			const real_t& x_loc = x0+(j+1)*dx;
			
			//Here we see the real utility of SYMD: there is no need to
			// implement the jacobian terms that populate "lhs"!
			rhs[j]    = rhs_func(ul=u[j], uc=u[j+1], ur=u[j+2], x=x_loc);
			lhs(j,-1) = symd::ddx(rhs_func, ul)(ul=u[j], uc=u[j+1], ur=u[j+2], x=x_loc);
			lhs(j, 0) = symd::ddx(rhs_func, uc)(ul=u[j], uc=u[j+1], ur=u[j+2], x=x_loc);
			lhs(j, 1) = symd::ddx(rhs_func, ur)(ul=u[j], uc=u[j+1], ur=u[j+2], x=x_loc);
		}
		
		//solve linear system
		auto du = example::tdma_solve_inplace(lhs,rhs);
		err = 0.0;
		for (int j = 0; j < n; ++j)
		{
			u[j+1] -= du[j];
			err += (du[j]*du[j]);
		}
		err = std::sqrt(err);
		err /= n;
		std::cout << err << std::endl;
	}
	
	//output solution
	std::ofstream myfile("out.csv");
	for (auto y:u) myfile << y << "\n";
	
	return 0;
}