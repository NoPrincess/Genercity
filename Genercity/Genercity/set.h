#pragma once
#include <iostream>
#include "tree_iterator.h"

template<typename T>
struct tree_node
{
	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	T value;
	tree_node *parent;
	tree_node *left;
	tree_node *right;

	tree_node(T const &value, tree_node *parent, tree_node *left, tree_node *right)
		: value(value), parent(parent), left(left), right(right) {}
	~tree_node()
	{
		if (left)
			delete left;
		if (right)
			delete right;
	}
};

template<typename T>
class set
{
	typedef tree_node<T> node_type;
	node_type *root;
public:
	typedef T value_type;
	typedef tree_iterator<node_type> const_iterator;
	
	set() : root() {}
	~set()
	{
		if (root)
			delete root;
	}

	///尝试向集合中插入值，返回是否成功插入，
	///当集合中已有该值时返回false，否则返回true。
	bool insert(T const &v)
	{
		node_type **n = &root;
		node_type *p = 0;
		while (*n)
		{
			if (v == (*n)->value)
				return false;
			else
			{
				p = *n;
				n = v < (*n)->value ? &((*n)->left) : &((*n)->right);
			}
		}
		*n = new node_type(v, p, 0, 0);
		return true;
	}

	bool has(T const &v)
	{
		node_type *n = root;
		while (n)
		{
			if (v == n->value)
				return true;
			n = v < n->value ? n->left : n->right;
		}
		return false;
	}

	bool is_empty() const
	{
		return root == 0;
	}

	const_iterator begin() const
	{
		node_type *n = root;
		while (n->left)
			n = n->left;
		return const_iterator(n);
	}
	
	const_iterator end() const
	{
		return const_iterator();
	}
};