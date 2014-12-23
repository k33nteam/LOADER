#pragma once

#include <sal.h>

class IExecAllocator
{
public:
	virtual
	void
	XFree(
		__inout unsigned char* execMem
		) = 0;

	virtual
	__checkReturn
	unsigned char*
	XAlloc(
		__in size_t size
		) = 0;
};

class CExecAllocator :
	public IExecAllocator
{
protected:
	const void* m_allocx;
	const void* m_freex;

	CExecAllocator(
		__in const void* kernel,
		__in const char* alloc,
		__in const char* free
		);
};
