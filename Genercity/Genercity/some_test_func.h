#pragma once
#include "pool_allocator.h"
#include "test_suite.h"
#include <list>
using std::list;

#include <iostream>
#include <sstream>
using July::pool_allocator;

typedef list<size_t, pool_allocator<size_t>> pool_list;
typedef list<size_t> normal_list;

void print_test_result(test_result const &result)
{
	std::ostringstream oss_insertion, oss_deletion;
	float total = 0;
	for (test_result::const_iterator i = result.begin(); i < result.end(); i++)
	{
		oss_insertion << '\t' << i->first;
		oss_deletion << '\t' << i->second;
		total += i->first + i->second;
	}
	std::cout << "Insertion time:" << oss_insertion.str() << std::endl
		<< "Deletion time:" << oss_deletion.str() << std::endl;
}

void test_pool_allocate()
{
	std::cout << "============== my pool list ============" << std::endl;
	print_test_result(run_test_suit<pool_list>());

	std::cout << July::pool_allocator_recycle() << " bytes recycled." << std::endl;

	std::cout << "============== normal list =============" << std::endl;
	print_test_result(run_test_suit<normal_list>());
}