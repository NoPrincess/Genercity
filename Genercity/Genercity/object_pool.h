#pragma once
#include <cstddef>
#include <algorithm>
#include <new>
#include <memory>

#ifndef MYLIB_NUM_NODES_PER_CHUNK
#define MYLIB_NUM_NODES_PER_CHUNK 128
#endif

namespace July
{
	class object_pool
	{
		static const unsigned char num_nodes_per_chunk = MYLIB_NUM_NODES_PER_CHUNK;
		typedef unsigned char counter_type;
		struct chunk_data
		{
			counter_type free_node_count;
			chunk_data *next;
		};
		static const size_t chunk_data_size = sizeof(chunk_data);

		chunk_data *chunk_data_head;

		struct free_node
		{
			counter_type bias;
			free_node *next;
		};

		static const size_t free_node_offset = offsetof(free_node, next);

		free_node *free_node_head;

		const size_t node_size;
		const size_t free_node_size;
		const size_t chunk_size;

	public:
		object_pool(size_t node_size) :
			chunk_data_head(0), free_node_head(0),
			node_size(node_size),
			free_node_size(free_node_offset + std::max(sizeof(free_node*), node_size)),
			chunk_size(chunk_data_size + free_node_size * num_nodes_per_chunk) {}
		~object_pool()
		{
			while (chunk_data_head)
			{
				chunk_data *chunk = chunk_data_head;
				chunk_data_head = chunk_data_head->next;
				operator delete(chunk);
			}
		}

		void* allocate() throw (std::bad_alloc);
		void deallocate(void *ptr);
		size_t recycle(); //释放空闲组块
	};

	class object_pool_array
	{
		size_t sz;
		object_pool *array;
	public:
		///sz为对象池格式，step为各对象池尺寸之差
		///e.g. sz = 4, step = 8 则4个对象池尺寸依次为: 8, 16, 32, 40
		object_pool_array(size_t sz, size_t step) : sz(sz),
			array(static_cast<object_pool*>(operator new (sizeof(object_pool) * sz)))
		{
			for (size_t i = 0; i < sz; i++)
				new (array + i) object_pool(i * step + step);
		}
		~object_pool_array()
		{
			for (size_t i = 0; i < sz; i++)
				(array + i)->~object_pool();
			operator delete (array);
		}
		size_t size() const
		{
			return sz;
		}
		object_pool& operator[](size_t n)
		{
			return array[n];
		}
	};

	template<typename T0, typename T1>
	inline T0* byte_shift(T1* ptr, size_t b)
	{
		return reinterpret_cast<T0*>(reinterpret_cast<char*)(ptr) + b);
	}

	void* object_pool::allocate() throw(std::bad_alloc)
	{
		if (!free_node_head)
		{
			chunk_data *new_chunk = reinterpret_cast<chunk_data*>(operator new (chunk_size));
			new_chunk->next = chunk_data_head;
			chunk_data_head = new_chunk;
			free_node_head = byte_shift<free_node>(new_chunk, chunk_data_size);
			free_node_head->bias = 0;
			free_node_head->next = 0;
			for (size_t node_index = 1; node_index < num_nodes_per_chunk; node_index++)
			{
				free_node *f = byte_shift<free_node>(free_node_head, free_node_size);
				f->bias = free_node_head->bias + 1;
				f->next = free_node_head;
				free_node_head = f;
			}
		}
		free_node *return_node = free_node_head;
		free_node_head = free_node_head->next;
		return static_cast<void*>(&(return_node->next));
	}

	void object_pool::deallocate(void* ptr)
	{
		free_node *f = byte_shift<free_node>(ptr, -1 * free_node_offset);
		f->next = free_node_head;
		free_node_head = f;
	}

	size_t object_pool::recycle()
	{
		size_t *shift_table = new size_t[num_nodes_per_chunk];
		shift_table[0] = -1 * chunk_data_size;
		for (size_t i = 1; i < num_nodes_per_chunk; i++)
		{
			shift_table[i] = shift_table[i - 1] - free_node_size;
		}

		//重置所有的chunk的free_node_count
		for (chunk_data *p = chunk_data_head; p; p = p->next)
		{
			p->free_node_count = 0;
		}
		for (free_node *f = free_node_head; f; f = f->next)
		{
			chunk_data *chunk = byte_shift<chunk_data>(f, shift_table[f->bias]);
			chunk->free_node_count++;
		}

		//将全空闲chunk的所属节点从free_list中删除
		for (free_node **pp = &free_node_head; *pp; )
		{
			chunk_data *chunk = byte_shift<chunk_data>(*pp, shift_table[(*pp)->bias]);
			if (chunk->free_node_count == num_nodes_per_chunk)
				*pp = (*pp)->next;
			else
				pp = &((*pp)->next);
		}

		//将所有空闲chunk从链表中删除
		size_t num_recycled = 0;
		for (chunk_data **pp = &chunk_data_head; *pp; )
		{
			if ((*pp)->free_node_count == num_nodes_per_chunk)
			{
				chunk_data *p = *pp;
				*pp = (*pp)->next;
				operator delete(p);
				num_recycled++;
			}
			else pp = &((*pp)->next);
		}
		delete[] shift_table;
		return num_recycled * chunk_size;
	}
}