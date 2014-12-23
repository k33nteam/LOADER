#pragma once

#include <sal.h>
#include "../ExecAllocator.h"

class CKernelAllocator :
	public CExecAllocator
{
public:
	CKernelAllocator(
		__in const void* kernel
		);

	void
	XFree(
		__inout unsigned char* execMem
		) override;

	__checkReturn
	unsigned char*
	XAlloc(
		__in size_t size
		) override;
};
