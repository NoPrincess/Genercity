#pragma once
#include <stdexcept>

template<typename T>
class my_vector
{
	T *array;
	unsigned size;
	unsigned block_size;
public:
	//my_vector(unsigned bsz) :
	//	array(new T[bsz]), size(0), block_size(bsz) {}
	my_vector(T Targs...)
	{
		try
		{
			array = new T[sizeof(Targs)];
		}
		catch(std::runtime_error &ex)
		{
			std::cerr << ex.what() << std::endl;
		}
		for (unsigned i = 0; i < sizeof(Targs); i++)
			array[i] = zip(Targs);
	}
	const T zip(const T& t)
	{
		return t;
	}
	~my_vector()
	{
		if (array)
		{
			free(array);
		}
	}
	void push_back(T const& elem) throw (std::runtime_error)
	{
		if (size == block_size)
		{
			block_size *= 2;
			T* new_array = (T*)realloc(array, block_size * sizeof(T));
			if (new_array != nullptr)
			{
				array = new_array;
			}
			else
			{
				free(array);
				array = nullptr;
				throw std::runtime_error("Out of memory.");
			}
		}
		array[size++] = elem;
	}

	T& operator[](unsigned i)
	{
		return array[i];
	}
	const T& operator[](unsigned i) const
	{
		return array[i];
	}
	unsigned get_mem_size() const
	{
		return block_size * sizeof(T);
	}
};


template<>
class my_vector<bool>
{
	int *array;
	unsigned size;
	unsigned block_size;
	const static unsigned seg_size;
public:
	my_vector(unsigned bsz = 1) : array(new int[bsz]), size(0), block_size(bsz) {}
	~my_vector()
	{
		if (array)
		{
			free(array);
		}
	}

	void push_back(bool elem) throw (std::runtime_error)
	{
		if (size == block_size * seg_size)
		{
			block_size *= 2;
			int* new_array = (int*)realloc(array, sizeof(int) * block_size);
			if (new_array != nullptr)
			{
				array = new_array;
			}
			else
			{
				free(array);
				array = nullptr;
				throw std::runtime_error("Out of memory.");
			}
		}
		set(size++, elem);
	}

	void set(unsigned i, bool elem)
	{
		if (elem)
		{
			array[i / seg_size] |= (0x1 << (i % seg_size));
		}
		else
		{
			array[i / seg_size] &= ~(0x1 << (i % seg_size));
		}
	}

	bool operator[] (unsigned i) const
	{
		return (array[i / seg_size] & (0x1 << (i % seg_size))) != 0;
	}

	unsigned get_mem_size() const
	{
		return block_size * sizeof(int);
	}
};
const unsigned my_vector<bool>::seg_size = sizeof(int) * 8;  