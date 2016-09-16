#pragma once
#include <iostream>
///�����ֵ 1.1
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

///�����Ƶ� 1.2
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

///foreach, �����������Լ������δ�ӡ�ַ��� 1.3
///����ָ��ģ�����
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

///ָ�뼰����ģ����� 1.4
///1.��ָ����Ϊģ�����
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
///2.��������Ϊģ�����
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

///��Ա����ָ��ģ����� 1.5
///�������������ͬһ�����͵Ĳ������䷵��ֵ��ͬ���ɶ���һָ����һϵ�г�Ա������ָ�롣
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
template<some_value_mfp func> //func��һ����Ա����ָ����ģ�����
int call(some_value &value, int op)
{
	return (value.*func)(op);
}

///��ʹ��ѭ���������ж���䣬��ӡ1-N������ 1.6
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
