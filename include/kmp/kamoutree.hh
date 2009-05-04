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
// kamoutree
// ---------
//
// Static tree
// ----------------------------------------------------------------------------

#ifndef _KMP_KAMOUTREE_HH_
#define _KMP_KAMOUTREE_HH_



namespace kmp
{

template<typename DataT>
struct leaf_
{
	typedef DataT data_t;
}

template<typename DataT, typedef LeftT, typedef RightT>
struct sn
{
	typedef DataT data_t;
	typedef LeftT left_t;
	typedef RightT right_t;
};

} // namespace kmp



#endif
