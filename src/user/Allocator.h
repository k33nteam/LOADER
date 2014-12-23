#pragma once

#include <sal.h>
#include "../ExecAllocator.h"

class CUserAllocator :
	public CExecAllocator
{
public:
	CUserAllocator(
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
