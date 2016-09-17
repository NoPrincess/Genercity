#include "test.h"
#include "heteroList.h"
#include "my_vector.h"
#include "list.h"
#include "tree_iterator.h"
#include "algorithms.h"
#include <string>

void test1_1();
void test1_2();
void testHeteroList();
void test1_3();
void test1_4();
void test1_5();
void testMyVector();
void test1_6();
void testIterator();

int main()
{
	testIterator();
	system("PAUSE");
	return 0;
}

void test1_1()
{
	int l[] = { 2, 0, 1, 1, 0, 8, 2, 5 };
	char cl[] = "August";
	std::cout << max_element<int>(l, 8) << std::endl;
	std::cout << max_element<char>(cl, 6) << std::endl;
}

void test1_2()
{
	double sv2;
	
	sv2 = func<double, int, int>(1, 2, 3);
	std::cout << "\tsv2: " << sv2 << std::endl;

	sv2 = func<double, int, int>(1, 2, 3);
	std::cout << "\tsv2: " << sv2 << std::endl;

	sv2 = func<double, int, int>(1, 0.1, 0.1);
	std::cout << "\tsv2: " << sv2 << std::endl;

	sv2 = func<int, double, double>(0.1, 0.1, 0.1);
	std::cout << "\tsv2: " << sv2 << std::endl;
}

void testHeteroList()
{
	typedef hetero_node<int, void> node_0;
	typedef hetero_node<char, node_0> node_1;
	typedef hetero_node<std::string, node_1> node_2;

	node_2 *p2 = push(std::string("Awsome!"), push('a', push(1, (void*)0)));

	std::cout << p2->value << ", " << p2->next->value << ", " << p2->next->next->value << std::endl;

	pop(pop(pop(p2)));
}

void test1_3()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	using namespace myforeach;
	foreach<int, print<int> >(array, 8);
	std::cout << std::endl;
	
	foreach<int, inc<int> >(array, 8);
	foreach<int, print<int> >(array, 8);
	std::cout << std::endl;

	foreach<int, dec<int> >(array, 8);
	foreach<int, print<int> >(array, 8);
	std::cout << std::endl;
}

void test1_4()
{
	wrapper<&global_variable> gwrapper;
	gwrapper.set(1);
	std::cout << gwrapper.get() << std::endl;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      

	wrapper2 <global_variable> gwrapper2;
	gwrapper2.set(2);
	std::cout << gwrapper2.get() << std::endl;

	//局部变量指针或引用不可用于模板参数
	//int local_variable;
	//wrapper<local_variable> lwrapper;
}

void test1_5()
{
	some_value v0(0);
	std::cout << call<&some_value::add_by>(v0, 1) << std::endl;
	std::cout << call<&some_value::sub_by>(v0, 2) << std::endl;
	std::cout << call<&some_value::mul_by>(v0, 3) << std::endl;
}

void testMyVector()
{
	my_vector<char> vc(2);
	my_vector<bool> vb(2);
	for (unsigned i = 0; i < 20; i++)
	{
		vc.push_back('a' + i);
		vb.push_back(i % 4 == 0);
	}
	std::cout << "MemSize of my_vector<char> is " << vc.get_mem_size() << std::endl;
	std::cout << "MemSize of my_vector<bool> is " << vb.get_mem_size() << std::endl;
	for (unsigned i = 0; i < 20; i++)
	{
		std::cout << vc[i] << " ";
	}
	std::cout << std::endl;
	for (unsigned i = 0; i < 20; i++)
	{
		std::cout << vb[i] << " ";
	}
	std::cout << std::endl;
}

void test1_6()
{
	print<100>();
}

void testIterator()
{
	list<int> la, lb;
	for (int i = 0; i < 7; i++)
	{
		la.push_front(i * 2 % 7);
		lb.push_front(i * 2 % 7);
	}
	list<int>::iterator it = July::find(lb.begin(), lb.end(), 3);
	la.erase(it);    //容器与迭代器不一致，不涉及修改容器的链表头指针。
	July::print(la.begin(), la.end());
	July::print(lb.begin(), lb.end());
	it = July::find(lb.begin(), lb.end(), 5);
	la.erase(it);   //容器与迭代器不一致，且需要修改容器的链表头指针。
	July::print(la.begin(), la.end());
	July::print(lb.begin(), lb.end());
}

