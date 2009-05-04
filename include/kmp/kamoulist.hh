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
// kamoulist
// ---------
//
// Static lists of types, and associated run-time container.
// ----------------------------------------------------------------------------

#ifndef _KMP_KAMOULIST_HH_
#define _KMP_KAMOULIST_HH_



namespace kmp
{

	// --- LIST -------------------------------------------------------------------

	// END.
	template <typename V>
	struct end_
	{
		typedef V value_t;
	};

	// LIST.
	template <typename V, typename N>
	struct sl
	{
		typedef V value_t;
		typedef N next_t;
	};



	// --- SIZE -------------------------------------------------------------------

	// EVAL SIZE.
	template <typename L>
	struct eval_size
	{
		static const int size = sizeof (typename L::value_t)
			+ eval_size<typename L::next_t>::size;
	};

	template <typename V>
	struct eval_size<end_<V> >
	{
		static const int size = sizeof (typename end_<V>::value_t);
	};



	// NUM EL.
	template <typename L>
	struct num_el
	{
		static const int N = 1 + num_el<typename L::next_t>::N;
	};

	template <typename V>
	struct num_el<end_<V> >
	{
		static const int N = 1;
	};



	// --- ACCESS -----------------------------------------------------------------

	// ACCESS TYPE.
	template <int N, typename SL>
	struct access_type
	{
		typedef typename access_type<N-1, typename SL::next_t>::type_t type_t;
	};

	template<typename SL>
	struct access_type<0, SL>
	{
		typedef typename SL::value_t type_t;
	};



	// GET OFFSET.
	template <int N, typename SL>
	struct get_offset
	{
		static const int O = sizeof(typename SL::value_t) + get_offset<N-1, typename SL::next_t>::O;
	};

	template<typename SL>
	struct get_offset<0, SL>
	{
		static const int O = 0;
	};



	// --- KAMOULIST --------------------------------------------------------------

	template <typename SL>
	struct kamoulist
	{
		typedef SL list_t;
		static const int array_size = eval_size<SL>::size;

		// The pointer manipulation is dirty and generates warnings:
		// disable them temporarily.
#ifdef WIN32
# pragma warning(disable: 4311 4312)
#endif

		template<int N>
		typename access_type<N,list_t>::type_t get_elem()
		{
			const int offset = get_offset<N,list_t>::O;
			void* p = reinterpret_cast<void*>(reinterpret_cast<unsigned>(array) + offset);
			return *reinterpret_cast<typename access_type<N,list_t>::type_t*>(p);
		}

		template<int N>
		void set_elem(const typename access_type<N,list_t>::type_t& val)
		{
			const int offset = get_offset<N,list_t>::O;
			void* p = reinterpret_cast<void*>(reinterpret_cast<unsigned>(array) + offset);
			*reinterpret_cast<typename access_type<N,list_t>::type_t*>(p) = val;
		}

		// Reset normal level of warnings
#ifdef WIN32
# pragma warning(default: 4311 4312)
#endif

	private:
		unsigned char array[array_size];
	};

} // namespace kmp



#endif
