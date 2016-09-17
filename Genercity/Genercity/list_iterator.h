#pragma once
#include <stdexcept>

template<typename T> class list;

template<typename N>
class list_iterator
{
	N *pos;
	template<typename T> friend class list;
public:
	typedef typename N::value_type value_type;
	typedef typename N::reference_type reference_type;
	typedef typename N::const_reference_type const_reference_type;
	typedef list_iterator<N> self_type;

	list_iterator() : pos(0) {}
	list_iterator(N *pos) : pos(pos) {}
	bool operator!= (self_type const &right) const
	{
		return pos != right.pos;
	}
	bool operator==(self_type const &right) const
	{
		return pos != right.pos;
	}
	self_type& operator++ ()
	{
		if (pos)
			pos = pos->next;
		return *this;
	}
	reference_type operator* () throw (std::runtime_error)
	{
		if (pos)
			return pos->value;
		else
			throw (std::runtime_error("dereferencing null iterator!"));
	}
};