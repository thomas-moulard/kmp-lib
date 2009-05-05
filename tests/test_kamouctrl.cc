#include <iostream>

#include <kmp/kamouctrl.hh>
using namespace kmp;



void print() { std::cout << "print for kamouctrl" << std::endl; }
void print_int(int i) { std::cout << i << std::endl; }



// result is in 'val', so no need to adapt
template<int N>
struct fac { enum { val = N * fac<N-1>::val }; };

template<>
struct fac<0> { enum { val = 1 }; };



// oops, result is named 's', we will need an adapter
template<int N>
struct sumn { enum { s = N + sumn<N-1>::s }; };

template<>
struct sumn<0> { enum { s = 0 }; };

// adapter
template<int N>
struct tl_traits<sumn, N>
{
	enum { val = sumn<N>::s };
};



void test_kamouctrl()
{
	for_<0,3>::do_(print);
	for_<5,3>::do_(print); // should print nothing

	tfor_<0,3,fac>::do_(print_int);
	tfor_<0,3,sumn>::do_(print_int);
}
