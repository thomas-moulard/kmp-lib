#include <iostream>
#include <cstdlib>

#include <kmp/kamoulist.hh>
using namespace kmp;

// Disable unused variable warnings
#ifdef WIN32
# pragma warning(disable: 4101)
#endif

void test_kamoulist()
{
  {
    std::cout << "Reference:" << std::endl
	      << "  Char: " << sizeof (char) << std::endl
	      << "  Int: " << sizeof (int) << std::endl
	      << "  Float: " << sizeof (float) << std::endl
	      << "  Double: " << sizeof (double) << std::endl;
  }

  {
    typedef sl<float, end_<int> > slist_t;
    std::cout << eval_size<slist_t>::size << std::endl;

    kamoulist<slist_t> tmp;
  }

  {
    typedef sl<float, end_<int> > slist_t;
    std::cout << eval_size<slist_t>::size << std::endl;

    kamoulist<slist_t> tmp;
  }

  {
    typedef sl<float, sl<double, end_<int> > > slist_t;
    std::cout << eval_size<slist_t>::size << std::endl;

    kamoulist<slist_t> tmp;
  }

  {
    typedef sl<float, sl<double, sl<char, end_<int> > > > slist_t;
    std::cout << "Total list size: " << eval_size<slist_t>::size << std::endl;

    access_type<3,slist_t>::type_t lsize = num_el<slist_t>::N;
    std::cout << "Num. elements: " << lsize << std::endl;

    std::cout << "type[0] size: " << sizeof(access_type<0,slist_t>::type_t) << std::endl;
    std::cout << "type[1] size: " << sizeof(access_type<1,slist_t>::type_t) << std::endl;
    std::cout << "type[2] size: " << sizeof(access_type<2,slist_t>::type_t) << std::endl;
    std::cout << "type[3] size: " << sizeof(access_type<3,slist_t>::type_t) << std::endl;

    std::cout << "offset for elm 2: " << get_offset<2,slist_t>::O << std::endl;

    kamoulist<slist_t> tmp;
    tmp.set_elem<0>(2.0);
    tmp.set_elem<1>(1e-12);
    tmp.set_elem<2>('a');
    tmp.set_elem<3>(3);

    std::cout << "Values: "
	      << tmp.get_elem<0>() << " "
	      << tmp.get_elem<1>() << " "
	      << tmp.get_elem<2>() << " "
	      << tmp.get_elem<3>() << std::endl;
  }
}

// Restore unused variable warnings
#ifdef WIN32
# pragma warning(default: 4101)
#endif
