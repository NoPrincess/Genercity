#pragma once
#include "list_iterator.h"

template<typename T>
struct list_node
{
	typedef T value_type;
	typedef T& reference_type;
	typedef const T& const_reference_type;

	T value;
	list_node *prev;
	list_node *next;
	list_node (T const &value, list_node *prev, list_node *next) : value(value), prev(prev), next(next) {}
};

template<typename T>
class list
{
	typedef list_node<T> node_type;
	node_type *head;
public:
	typedef T value_type;
	typedef list_iterator<node_type> iterator;
	list() : head() {}
	~list()
	{
		while (head)
		{
			node_type *n = head;
			head = head->next;
			delete n;
		}
	}
	void push_front(T const &v)
	{
		head = new node_type(v, 0, head);
		if (head->next)
		{
			head->next->prev = head;
		}
	}
	void pop_front(T const &v)
	{
		if (head)
		{
			node_type *n = head;
			head = head->next;
			head->prev = 0;
			delete n;
		}
	}
	void insert(iterator it, T const &v)
	{
		node_type *n = it.pos;
		if (n)
		{
			node_type *new_node = new node_type(v, n, n->next);
			new_node->next->prev = new_node;
			n->next = mew_node;
		}
	}
	void erase(iterator &it)
	{
		node_type *n = it.pos;
		++it;
		if (n)
		{
			if (n->next)
				n->next->prev = n->prev;
			if (n->prev)
				n->prev->next = n->next;
			if (head == n)
				head = n->next;
			delete n;
		}
	}
	bool is_empty() const
	{
		return head == 0;
	}
	iterator begin()
	{
		return iterator(head);
	}
	iterator end()
	{
		return iterator();
	}
};