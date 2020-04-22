#include "n_heap.h"

#include "core_globals.h"
#include "n_iostream.h"

unsigned char pseudoHeap[1024 * 1024 * 10];
size_t bytesUsed = 0;

void* malloc(size_t size)
{
	void* ret = (void*)&(pseudoHeap[bytesUsed]);
	bytesUsed += size;

	if (bytesUsed >= sizeof(pseudoHeap))
		pink_screen_of_death();

	return ret;
}

void free(void* ptr)
{
	//okay mazafaka
}

inline void* operator new(size_t size)
{
	return malloc(size);
}

inline void* operator new[](size_t size)
{
	return malloc(size);
}

inline void* operator new(size_t size, void* ptr)
{

}

inline void* operator new[](size_t size, void* ptr)
{

}

inline void operator delete(void* ptr)
{
	return free(ptr);
}

inline void operator delete[](void* ptr)
{
	return free(ptr);
}

inline void operator delete(void* ptr, size_t size)
{
	return free(ptr);
}

inline void operator delete[](void* ptr, size_t size)
{
	return free(ptr);
}