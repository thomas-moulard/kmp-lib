#include <iostream>

#ifdef WIN32
# include <cstdlib>
#endif

#include <kmp/kamoutil.hh>
using namespace kmp;



struct ppa { static void f() { std::cout << "ppa"; } };
struct pa: public ppa { static void f() { std::cout << "pa"; } };
struct a: public pa { static void f() { std::cout << "a"; } };

struct ppb { static void f() { std::cout << "ppb"; } };
struct pb: public ppb { static void f() { std::cout << "pb"; } };
struct b: public pb { static void f() { std::cout << "b"; } };

template<> struct base_traits<a> { typedef pa base_t; };
template<> struct base_traits<pa> { typedef ppa base_t; };
template<> struct base_traits<b> { typedef pb base_t; };
template<> struct base_traits<pb> { typedef ppb base_t; };



namespace kmp
{
	template<>
	class til_<type<ppa, black>, type<ppb, black> >
	{
	public:

		virtual void f() { std::cout << "Top-node, default behavior" << std::endl; }
	};

	class pa_b
		: public til<pa, b>::type_t
	{
	public:

		virtual void f()
		{
			std::cout << "Special behavior defined in class pa_b: ";
			pa::f(); std::cout << ", "; b::f(); std::cout << std::endl;
		}
	};
}



void print(til_a<ppa, ppb>::type_t& arg)
{
	arg.f();
}

void accept_only_rspec(til_r<ppa, ppb>::type_t& arg)
{
	arg.f();
}



#ifdef WIN32
# pragma warning(disable: 4101)
#endif


void test_kamoutil()
{
	// test base_traits
	{
		base_traits<a>::base_t::f(); std::cout << std::endl;
		base_traits<pb>::base_t::f();  std::cout << std::endl;
		// base_traits<ppa>::base_t::f(); // should not compile
	}


	// test type
	{
		type<undef_base, black> u_black;
		// type<undef_base, undef_base> t_fail; // should not compile
	}


	// test til
	{
		til<a, pb>::type_t derived1;
		til_a<ppa, ppb>::type_t* base = &derived1;
		// til_a<pa, b>::type_t* base2 = &derived1; // should not compile

		til<undef_base, undef_base>::type_t derived2;
		til<undef_base, b>::type_t derived3;
		til<a, undef_base>::type_t derived4;

		til_a<undef_base, undef_base>::type_t* ptr;
		ptr = &derived1;
		ptr = &derived2;
		ptr = &derived3;
		ptr = &derived4;
	}

	// advanced til
	{
		til<ppa, ppb>::type_t t0;
		til<a, b>::type_t t1;
		til<pa, b>::type_t t2;
		pa_b pab;

		print(t0);
		print(t1);
		print(t2);
		print(pab);
	}

	// more advanced til
	{
		til<ppa, pb>::type_t t1;
		til<ppa, b>::type_t t2;
		til<pa, pb>::type_t t3;
		til<a, pb>::type_t t4;
		pa_b pab;

		accept_only_rspec(t1);
		accept_only_rspec(t2);
		// accept_only_rspec(t3); // should not compile
		// accept_only_rspec(t4); // should not compile
		accept_only_rspec(pab);
	}


#ifdef WIN32
	system("pause");
#endif
}

#ifdef WIN32
# pragma warning(default: 4101)
#endif
