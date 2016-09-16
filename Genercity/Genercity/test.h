#pragma once
#include <iostream>
///求最大值 1.1
template<typename T>
T const& max_element(T const *l, unsigned sz)
{
	T const *max_value(l);
	for (unsigned i = 1; i < sz; i++)
	{
		if (l[i] > *max_value)
			max_value = &(l[i]);
	}
	return *max_value;
}

///类型推导 1.2
template<typename T0, typename T1, typename T2, typename T3, typename T4>
T2 func(T1 v1, T3 v3, T4 v4)
{
	T0 static sv0 = T0(0);
	T2 static sv2 = T2(0);
	std::cout << "\tv1: " << v1 << "\tv3: " << v3
		<< "\tv4: " << v4 << "\t || sv0: " << sv0;
	T2 v2 = sv2;
	sv0 -= 1;
	sv2 -= 1;
	return v2;
}

///foreach, 包括自增、自减、依次打印字符。 1.3
///函数指针模板参数
namespace myforeach
{
	template<typename T, void(*f) (T& v)>
	void foreach(T array[], unsigned size)
	{
		for (unsigned i = 0; i < size; i++)
		{
			f(array[i]);
		}
	}

	template<typename T>
	void inc(T& v)
	{
		v++;
	}

	template<typename T>
	void dec(T& v)
	{
		v--;
	}

	template<typename T>
	void print(T& v)
	{
		std::cout << ' ' << v;
	}
}

///指针及引用模板参数 1.4
///1.以指针作为模板参数
template<int *p>
struct wrapper
{
	int get()
	{
		return *p;
	}
	void set(const int v)
	{
		*p = v;
	}
};
///2.以引用作为模板参数
template<int &p>
struct wrapper2
{
	int get()
	{
		return p;
	}
	void set(const int v)
	{
		p = v;
	}
};
int global_variable = 0;

///成员函数指针模板参数 1.5
///多个函数都接受同一个类型的参数且其返回值相同，可定义一指向其一系列成员函数的指针。
class some_value
{
	int value;
public:
	some_value(int _value) : value(_value) {}
	int add_by(int op)
	{
		return value += op;
	}
	int sub_by(int op)
	{
		return value -= op;
	}
	int mul_by(int op)
	{
		return value *= op;
	}
};
typedef int (some_value::* some_value_mfp)(int);
template<some_value_mfp func> //func是一个成员函数指针型模板参数
int call(some_value &value, int op)
{
	return (value.*func)(op);
}

///不使用循环及条件判断语句，打印1-N的数字 1.6
template<int i>
void print()
{
	print<i - 1>();
	std::cout << i << std::endl;
}
template<>
void print<1>()
{
	std::cout << 1 << std::endl;
}
