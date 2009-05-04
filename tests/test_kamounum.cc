#include <iostream>

#include <kmp/kamounum.hh>
using namespace kmp;

void test_kamounum()
{
	// test int
	{
		std::cout << int_<5>::value << std::endl;
		std::cout << plus_<int_<5>, int_<6> >::res_t::value << std::endl;
	}

	// test monom
	{
		typedef monom_<int_<5>, x_, 2 > lhs_t;
		typedef monom_<int_<4>, x_, 2 > rhs_t;
		typedef plus_<lhs_t, rhs_t>::value res_t;
		display<res_t>(std::cout);
	}
}