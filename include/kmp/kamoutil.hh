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
// kamoutil
// --------
//
// Template inheritance lattice or graph
// ----------------------------------------------------------------------------

#ifndef _KMP_KAMOUTIL_HH_
#define _KMP_KAMOUTIL_HH_



namespace kmp
{

	// --- Inheritance traits -------------------------------------

	struct undef_base {};

	template<typename T>
	struct base_traits { typedef undef_base base_t; };



	// --- Colors -------------------------------------------------

	struct black {};
	struct red {};



	// --- Type ---------------------------------------------------

	template<typename T, typename C>
	struct type
	{
	private:
		type();
		type(const type<T, C>& t);
	};

	template<typename T>
	struct type<T, black>
	{
		typedef T type_t;
		typedef black color_t;
	};

	template<typename T>
	struct type<T, red>
	{
		typedef T type_t;
		typedef red color_t;
	};



	// --- til_ declaration ----------------------------------

	template<typename T1, typename T2>
	class til_
	{
		til_();
		til_(const til_<T1, T2>& tl);
	};



	// --- til_ end both branches ----------------------------

	// BLACK BLACK
	template<>
	class til_<type<undef_base, black>, type<undef_base, black> >
	{
	};

	template<>
	class til_<type<undef_base, black>, type<undef_base, red> >
		: public til_<
		type<undef_base, black>,
		type<undef_base, black>
		>
	{
	};

	// RED RED
	template<>
	class til_<type<undef_base, red>, type<undef_base, red> >
		: public til_<
		type<undef_base, black>,
		type<undef_base, black>
		>
	{
	};

	template<>
	class til_<type<undef_base, red>, type<undef_base, black> >
		: public til_<
		type<undef_base, black>,
		type<undef_base, black>
		>
	{
	};



	// --- til_ end one branch -------------------------------

	template<typename T1>
	class til_<type<T1, red>, type<undef_base, black> >
		: public til_<
		type<typename base_traits<T1>::base_t, red>,
		type<undef_base, black>
		>
		, public til_<
		type<T1, black>,
		type<undef_base, black>
		>
	{
	};

	// RED RED
	template<typename T1>
	class til_<type<T1, red>, type<undef_base, red> >
		: public til_<
		type<typename base_traits<T1>::base_t, red>,
		type<undef_base, black>
		>
		, public til_<
		type<T1, black>,
		type<undef_base, black>
		>
	{
	};

	template<typename T1>
	class til_<type<T1, black>, type<undef_base, red> >
		: public til_<
		type<T1, black>,
		type<undef_base, black>
		>
	{
	};

	template<typename T2>
	class til_<type<undef_base, black>, type<T2, red> >
		: public til_<
		type<undef_base, black>,
		type<typename base_traits<T2>::base_t, red>
		>
		, public til_<
		type<undef_base, black>,
		type<T2, black>
		>
	{
	};

	// RED RED
	template<typename T2>
	class til_<type<undef_base, red>, type<T2, red> >
		: public til_<
		type<undef_base, black>,
		type<typename base_traits<T2>::base_t, red>
		>
		, public til_<
		type<undef_base, black>,
		type<T2, black>
		>
	{
	};

	template<typename T2>
	class til_<type<undef_base, red>, type<T2, black> >
		: public til_<
		type<undef_base, black>,
		type<T2, black>
		>
	{
	};



	// --- (til_;red;red) ----------------------------------

	// RED RED
	template<typename T1, typename T2>
	class til_<type<T1, red>, type<T2, red> >
		: public til_<
		type<typename base_traits<T1>::base_t, red>,
		type<typename base_traits<T2>::base_t, red>
		>
		, public til_<
		type<typename base_traits<T1>::base_t, red>,
		type<T2, black>
		>
		, public til_<
		type<T1, black>,
		type<typename base_traits<T2>::base_t, red>
		>
		, public til_<
		type<T1, black>,
		type<T2, black>
		>
	{
	};



	// --- (til_;red;black) --------------------------------

	template<typename T1, typename T2>
	class til_<type<T1, red>, type<T2, black> >
		: public til_<
		type<typename base_traits<T1>::base_t, red>,
		type<T2, black>
		>
		, public til_<
		type<T1, black>,
		type<T2, black>
		>
	{
	};



	// --- (til_;black;red) --------------------------------

	template<typename T1, typename T2>
	class til_<type<T1, black>, type<T2, red> >
		: public til_<
		type<T1, black>,
		type<typename base_traits<T2>::base_t, red>
		>
		, public til_<
		type<T1, black>,
		type<T2, black>
		>
	{
	};



	// --- (til_;black;black) ------------------------------

	// defined by the genral case



	// --- til_ general case ---------------------------------

	template<typename T1, typename C1, typename T2, typename C2>
	class til_<type<T1, C1>, type<T2, C2> >
	{
	};



	// --- til any derivation --------------------------------

	template<typename T1, typename T2>
	class til_a
	{
	public:

		typedef til_<type<T1, black>, type<T2, black> > type_t;
	};



	// --- left more derived ---------------------------------

	template<typename T1, typename T2>
	class til_l
	{
	public:

		typedef til_<type<T1, red>, type<T2, black> > type_t;
	};



	// --- right more derived --------------------------------

	template<typename T1, typename T2>
	class til_r
	{
	public:

		typedef til_<type<T1, black>, type<T2, red> > type_t;
	};



	// --- til symmetrically derived -------------------------

	template<typename T1, typename T2>
	class til_s
	{
	public:

		typedef til_<type<T1, red>, type<T2, red> > type_t;
	};



	// --- til concrete should be sym. derived ---------------

	template<typename T1, typename T2>
	class til
	{
	public:

		typedef til_<type<T1, red>, type<T2, red> > type_t;
	};

} // namespace til



#endif
