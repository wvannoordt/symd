#include "symd.h"
#include <iomanip>
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
	//Solves the problem
    // df / dt = -2sqrt(f-4)sin(t)
    //using BDF2 time integration.
    //
    //Note the use of automatic differentiation in computing the
    //Jacobian term for the Newton iteration!
	const double dt = 1e-4;
	const double t0 = 0.0;
	const std::size_t nt = 15000;
	const int max_inner_its = 50;
	const auto abs = [](double a) -> double {return a<0?-a:a;};
	const double tol = 1e-10;
	double time = t0;
	double q_prev    = std::cos(t0-dt)*std::cos(t0-dt)+4.0;
	double q_current = std::cos(t0)*std::cos(t0)+4.0;
	std::cout << std::setprecision(15);
	std::ofstream myfile("out.csv");
	myfile << std::setprecision(15);
	for (int n = 0; n < nt; ++n)
	{
		bool inner_converged = false;
		int inner_its = 0;
		double eps = 1e50;
		double psol = q_current;
		
		
		enum syms {pv,qv,tv};
		
		symd::var_t<pv> p;
		symd::var_t<qv> q;
		symd::var_t<tv> t;
		
		auto rhs    = -2*symd::sqrt(q-4)*symd::sin(t);
		auto p_rhs  = 3*p-4*q_current+q_prev-2*dt*rhs(q=p);
		auto p_rhsj = symd::ddx(p_rhs,p);
		
		while (!inner_converged)
		{
			double a0 = p_rhs (t=time+dt, p=psol);
			double a1 = p_rhsj(t=time+dt, p=psol);
			eps = a0;
			psol = psol - eps/a1;
			inner_its++;
			inner_converged = ((abs(eps)<tol) || (inner_its>max_inner_its));
		}
		q_prev    = q_current;
		q_current = psol;
		myfile << time << ", " << q_current << ", " << std::cos(time)*std::cos(time)+4.0 << "\n";
		time += dt;
	}	
	return 0;
}