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
// kamouctrl
// ---------
//
// Control of execution
// ----------------------------------------------------------------------------

#ifndef _KMP_KAMOUCTRL_HH_
#define _KMP_KAMOUCTRL_HH_



namespace kmp
{

	// run-time 'if' with compile-time conditions.
	template<bool cond>
	struct if_
	{
		template<typename Fn> static void do_(Fn& fn) {}
	};

	template<>
	struct if_<true>
	{
		template<typename Fn> static void do_(Fn& fn) { fn(); }
	};



	// run-time 'for' with compile-time unrolling.
	template<int S, int E>
	struct for_
	{
		template<typename Fn>
		static void do_(Fn& fn)
		{
			if_<(S<E)>::do_(for_impl(fn));
		}

	private:

		template<typename Fn>
		struct for_impl_t
		{
			for_impl_t(Fn& fn): fn_(fn) {}
			void operator()() { fn_(); for_<S+1,E>::do_(fn_); }
		private:
			Fn& fn_;
		};

		template<typename Fn>
		static for_impl_t<Fn> for_impl(Fn& fn) { return for_impl_t<Fn>(fn); }
	};



	// adapter for meta-function with one int argument.
	template<template<int> class X, int N>
	struct tl_traits
	{
		enum { val = X<N>::val };
	};

	// run-time 'for' with compile-time evaluation
	// of expression templated by the index of the loop.
	template<int S, int E, template<int> class X>
	struct tfor_
	{
	public:

		template<typename Fn>
		static void do_(Fn& fn)
		{
#ifndef ALTERNATIVE_TFOR_IMPLEMENTATION
			if_<(S<E)>::do_(tfor_impl(fn));
#else
			tfor_impl<S, E>::do_(fn); // to use with alternative implementation
#endif
		}

	private:

#ifndef ALTERNATIVE_TFOR_IMPLEMENTATION

		template<typename Fn>
		struct tfor_impl_t
		{
			tfor_impl_t(Fn& fn): fn_(fn) {}
			void operator()() { fn_(tl_traits<X,S>::val); tfor_<S+1,E,X>::do_(fn_); }
		private:
			Fn& fn_;
		};

		template<typename Fn>
		static tfor_impl_t<Fn> tfor_impl(Fn& fn) { return tfor_impl_t<Fn>(fn); }

#else // !ALTERNATIVE_TFOR_IMPLEMENTATION

		template<int S, int E, bool cond>
		struct tfor_impl
		{
			template<typename Fn> static void do_(Fn& fn) {};
		};

		template<int S, int E>
		struct tfor_impl<S, E, true>
			: public tfor_impl<S+1, E, ((S+1)<E)>
		{
			typedef tfor_impl<S+1, E, ((S+1)<E)> mother_t;
			enum { i = S };

			template<typename Fn>
			static void do_(Fn& fn)
			{
				fn(tl_traits<X,i>::val);
				mother_t::do_(fn);
			}
		};

#endif // !ALTERNATIVE_TFOR_IMPLEMENTATION
	};

}



#endif