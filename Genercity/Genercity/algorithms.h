#pragma once
#include <iostream>

namespace July
{
	template<typename T>
	struct iterator_traits
	{
		typedef typename T::value_type value_type;
	};

	template<typename U>
	struct iterator_traits<U*>
	{
		typedef U value_type;
	};

	template<typename T>
	void print(T begin, T end)
	{
		if (begin != end)
		{
			std::cout << *begin;
			for (++begin; begin != end; ++begin)
			{
				std::cout << ' ' << *begin;
			}
			std::cout << std::endl;
		}
	}

	template<typename T>
	typename iterator_traits<T>::value_type sum(T begin, T end)
	{
		typename iterator_traits<T>::value_type value_type;
		value_type sum(0);
		for (; begin != end; begin++)
		{
			sum += *begin;
		}
		return sum;
	}

	///指定范围内数据循环移位
	template<typename T>
	void shift(T begin, T end)
	{
		typename iterator_traits<T>::value_type value_type;
		T it = begin;
		if (it != end)
		{
			value_type v = *begin, tmp;
			for (++it, it != end; it++)
			{
				tmp = *it;
				*it = v;
				v = tmp;
			}
			*begin = v;
		}
		return;
	}

	template<typename T>
	T find(T begin, T end, typename T::value_type const &v)
	{
		for (; begin != end; ++begin)
		{
			if (*begin == v)
				break;
		}
		return begin;
	}
}