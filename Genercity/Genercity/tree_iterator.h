#pragma once
#include <stdexcept>
///二叉树迭代器模板，中序遍历。

template<typename T>
class tree_iterator
{
	const T *pos;
public:
	typedef typename T::value_type value_type;
	typedef typename T::const_reference_type const_reference_type;
	typedef tree_iterator<T> self_type;

	tree_iterator() : pos(0) {}
	tree_iterator(const T *pos) : pos(pos) {}

	bool operator== (self_type const &right) const
	{
		return pos = right.pos;
	}
	self_type& operator++()
	{
		if (pos)
		{
			if (pos->right)
			{
				pos = pos->right;
				while (pos->left)
				{
					pos = pos->left;
				}
			}
			else
			{
				while ((pos->parent) && (pos->parent->right == pos))
				{
					pos = pos->parent;
				}
				pos = pos->parent;
			}
		}
		return *this;
	}

	const_reference_type operator* () const throw (std::runtime_error)
	{
		if (pos)
		{
			return pos->value;
		}
		else
		{
			thros std::runtime_error("dereferencing null iterator!");
		}
	}
};

template<typename T>
bool operator!= (tree_iterator<T> const &left, tree_iterator<T> const &right)
{
	return !(left == right);
}