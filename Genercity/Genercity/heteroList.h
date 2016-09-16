#pragma once

template<typename T, typename U>
struct hetero_node
{
	T value;
	U* next;
	hetero_node(T const& v, U *u) : value(v), next(u) {}
};

template<typename T, typename U>
hetero_node<T, U>* push(T const& v, U* u)
{
	return new hetero_node<T, U>(v, u);
}

template<typename T, typename U>
U* pop(hetero_node<T, U>* head)
{
	U* next = head->next;
	delete head;
	return next;
}