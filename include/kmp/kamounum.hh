// ----------------------------------------------------------------------------
// kmp
// ===
//
// Authors: Evrard & Moulard (rhymes!)
//
// Disclaimer:
//  Authors do not certify they were in full possession of their
//  minds when they created this piece of work. Actually, we have
//  reasons to believe they were drunk.
//
// Important note:
//  If by chance you find any use for this code, and don't find
//  it ugly, you might have to see a doctor. If you are not convinced,
//  please have a look at the element access in class kamoulist.
//
// Note:
//  This project will be subject to a proposal for inclusion in Boost,
//  if the authors appear to be drunk enough again.
//
// kamounum
// --------
//
// Meta numbers and operations
// ----------------------------------------------------------------------------

#ifndef _KMP_KAMOUNUM_HH_
#define _KMP_KAMOUNUM_HH_

#include <iostream>



namespace kmp
{

	struct uneval_ {};

	struct x_{ static void display(std::ostream& os) { os << "x"; } };

	template<int N_>
	struct int_
	{
		enum { value = N_ };
	};

	template<typename coefT, typename varT, int POW_>
	struct monom_
	{
		typedef coefT coef_t;
		typedef varT var_t;
		enum { POW = POW_ };
	};

	template<typename LH, typename RH>
	struct plus_
	{
		typedef LH lh_t;
		typedef RH rh_t;
	};

	template<int N_, int M_>
	struct plus_<int_<N_>, int_<M_> >
	{
		typedef int_<N_> lh_t;
		typedef int_<M_> rh_t;
		typedef int_<N_ + M_> res_t;
	};

	template<typename coefLT, typename coefRT, typename varT, int POW_>
	struct plus_<monom_<coefLT, varT, POW_>, monom_<coefRT, varT, POW_> >
	{
		typedef typename monom_<coefLT, varT, POW_> lh_t;
		typedef typename monom_<coefRT, varT, POW_> rh_t;

		typedef typename monom_<
			typename plus_<coefLT, coefRT>::res_t,
			varT,
			POW_
		> value;
	};

	template<typename T>
	struct display_traits
	{
		static void display(std::ostream& os) { os << "?"; }
	};

	template<>
	struct display_traits<x_>
	{
		static void display(std::ostream& os) { os << "x"; }
	};

	template<>
	struct display_traits<uneval_>
	{
		static void display(std::ostream& os) { os << "unevaluated-expression"; }
	};

	template<typename coefT, typename varT, int POW_>
	struct display_traits<monom_<coefT, varT, POW_> >
	{
		static void display(std::ostream& os)
		{
			os << coefT::value << " ";
			display_traits<varT>::display(os);
			os << "^" << POW_;
		}
	};

	template<typename T>
	void display(std::ostream& os)
	{
		display_traits<T>::display(os);
	}

} // namespace kmp



#endif
