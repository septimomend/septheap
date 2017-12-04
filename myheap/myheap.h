#pragma once

#include "stdafx.h"

namespace septmem
{

#define HEAP_SIZE 52428800

	// global
	//
	static unsigned char* heapmem = (unsigned char*)malloc(HEAP_SIZE);	// reserve 50Mb 
	static size_t bytes = 0;					// address counter

	struct heapmap
	{
		size_t used = 0, free = 0;
		unordered_map<void*, size_t> byteadd;
	} hmap;

	// prototypes
	//
	void* my_malloc(size_t size);
	void* my_realloc(void* pointer, size_t newsz);
	void my_free(void* pointer);

	void* my_memcpy(void* hither, const void* from, size_t size);
	void* my_memmove(void* hither, const void* from, size_t size);
	void* my_memset(void* pointer, int val, size_t howmany);

	// definition
	//

	void* my_malloc(size_t size)
	{
		void *p;

		// check free memory
		//
		if (HEAP_SIZE - bytes < size)
			return nullptr;

		p = &heapmem[bytes];		// allocate memory
		bytes += size;			// shift of the beginning for allocation 

		hmap.used += size;
		hmap.free = HEAP_SIZE - hmap.used;

		// store first address value and size of allocated memory to map
		//
		hmap.byteadd.insert(pair<void*, size_t>(p, size));

		return p;
	}

	void* my_realloc(void* pointer, size_t newsz)
	{
		size_t size = 0;

		// if nullptr - allocate memory with newsz bytes
		//
		if (pointer == nullptr)
			return my_malloc(newsz);

		// if zero bytes - free memory
		//
		if (newsz == 0)
		{
			my_free(pointer);
			return my_malloc(newsz);
		}

		// reallocate memory
		//
		void* reptr = my_malloc(newsz);
		
		// get memory size
		//
		unordered_map<void*, size_t>::const_iterator iter;
		iter = hmap.byteadd.find(reptr);
		if (iter != hmap.byteadd.end())
			size = iter->second;

		my_memcpy(reptr, pointer, size);

		my_free(pointer);

		hmap.used += newsz - size;
		hmap.free = HEAP_SIZE - hmap.used;

		return reptr;
	}

	void my_free(void* pointer)
	{
		if(pointer == nullptr)
			return;

		unordered_map<void*, size_t>::const_iterator iter;
		iter = hmap.byteadd.find(pointer);
		
		// if found
		//
		if (iter != hmap.byteadd.end())
		{
			// make data zero
			//
			char* del = (char*)iter->first;
			*del = '\0';

			hmap.used -= iter->second;
			hmap.free += iter->second;

			hmap.byteadd.erase(iter); // erase data
		}
		else
		{
			cout << "\n>> [error] my_free(): memory is already freed or not allocated by malloc or realloc\n" << endl;
			return;
		}
	}

	void* my_memcpy(void* hither, const void* from, size_t size)
	{
		// if size is 0
		// just return pointer without copied data
		//
		if (size != 0)
		{
			char* dest = (char*)hither;
			char* src = (char*)from;

			for (size_t i = 0; i < size; ++i)
				dest[i] = src[i];
		}

		return hither;
	}


	void* my_memmove(void* hither, const void* from, size_t size)
	{
		if (size == 0)
			return hither;

		char* dest = (char*)hither;
		char* src = (char*)from;
		char* temp = (char*)my_malloc(size); // a temporary array to hold data of src

		// ñopy data
		//
		for (int i = 0; i < size; i++)
			temp[i] = src[i];

		// ñopy data from temp to dest
		//
		for (int i = 0; i < size; i++)
			dest[i] = temp[i];

		my_free(temp);

		return hither;
	}

	void* my_memset(void* pointer, int val, size_t howmany)
	{
		if (howmany != 0)
		{
			int* ch = (int*)pointer;

			for (size_t i = 0; i < howmany; ++i)
				ch[i] = val;
		}

		return pointer;
	}

} // namespace end