#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

/////////////////////////////////////////////////////////////////////////////////////////////
///////////////// Tiago Costa, 2013              
/////////////////////////////////////////////////////////////////////////////////////////////

#include "Allocator.h"

class PoolAllocator : public Allocator
{
public:
	PoolAllocator(size_t objectSize, uint8 objectAlignment, size_t size, void* mem);
	~PoolAllocator();

	void* allocate(size_t size, uint8 alignment) override;
		
	void deallocate(void* p) override;

private:
	PoolAllocator(const PoolAllocator&); //Prevent copies because it might cause errors
	PoolAllocator& operator=(const PoolAllocator&);

	size_t     _objectSize;
	uint8         _objectAlignment;

	void**     _free_list;
};

namespace allocator
{
	inline PoolAllocator* newPoolAllocator(size_t objectSize, uint8 objectAlignment, size_t size, Allocator& allocator)
	{
		void* p = allocator.allocate(size+sizeof(PoolAllocator), __alignof(PoolAllocator));
		return new (p) PoolAllocator(objectSize, objectAlignment, size, pointer_math::add(p, sizeof(PoolAllocator)));
	}

	inline void deletePoolAllocator(PoolAllocator& poolAllocator, Allocator& allocator)
	{
		poolAllocator.~PoolAllocator();

		allocator.deallocate(&poolAllocator);
	}
};

#endif