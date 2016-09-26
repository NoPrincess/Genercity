#pragma once
#include <new>
#include <memory>
#include "object_pool.h"

#ifndef MYLIB_POOL_ALLOCATOR_SIZE_STEP
#define MYLIB_POOL_ALLOCATOR_SIZE_STEP 8
#endif // !MYLIB_POOL_ALLOCATOR_SIZE_STEP
#ifndef MYLIB_POOL_ALLOCATOR_POOL_SIZE
#define MYLIB_POOL_ALLOCATOR_POOL_SIZE 64
#endif // !MYLIB_POOL_ALLOCATOR_POOL_SIZE

namespace July
{
	class pool_allocator_base
	{
	public:
		static const size_t align = MYLIB_POOL_ALLOCATOR_SIZE_STEP;
		static const size_t pool_size = MYLIB_POOL_ALLOCATOR_POOL_SIZE;
		static const size_t max_size = align * pool_size;
		static object_pool_array pool;

		void* base_allocate(size_t n) throw (std::bad_alloc)
		{
			if (n == 0)
				throw std::bad_alloc();
			else if (n > max_size)
				return static_cast<void*>(operator new (n));
			else return pool[(n + align - 1) / align - 1].allocate();
		}
	};
}