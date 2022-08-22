#pragma once

namespace example
{
    //"tri-diagonal matrix" type
    template <typename data_t> struct tridiag_t
    {
    	std::vector<data_t> data;
    	tridiag_t(){}
    	tridiag_t(const std::size_t& size, const data_t& init){data.resize(3*size, init);}
        std::size_t size() const {return data.size()/3;}
    	data_t& operator()(int i, int j) {return data[3*i+(j+1)];}
    	const data_t& operator()(int i, int j) const {return data[3*i+(j+1)];}
    	void set_diag(int j, const data_t& val)
    	{
    		for (int i = 0; i < data.size()/3; ++i) (*this)(i,j) = val;
    	}
    };

    template <typename data_t> static std::vector<data_t> tdma_solve_inplace(tridiag_t<data_t>& lhs, std::vector<data_t>& rhs)
    {
    	const auto num = lhs.size();
    	for (int i = 1; i < num; i++)
    	{
    		lhs(i,-1)  /= lhs(i-1,0); //wi (store on subdiagonal)
    		lhs(i,0)   -= lhs(i,-1)*lhs(i-1,1); //bi = bi - wi*c(i-1)
    		rhs[i]     -= lhs(i,-1)*rhs[i-1];
    	}
    	rhs[num-1] /= lhs(num-1,0);
    	for (int i = num-2; i >= 0; i--) rhs[i] = (rhs[i] - lhs(i,1) * (rhs[i+1]))/lhs(i,0);
    	std::vector<data_t> output = rhs;
    	return output;
    }
}