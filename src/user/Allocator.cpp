#include "Allocator.h"

#include <windows.h>

CUserAllocator::CUserAllocator(
	__in const void* kernel
	) : CExecAllocator(kernel, "VirtualAlloc", "VirtualFree")
{
}

void
CUserAllocator::XFree(
	__inout unsigned char* execMem
	)
{
	reinterpret_cast<decltype(&VirtualFree)>(m_freex)(
		execMem,
		0,
		MEM_RELEASE);
}

__checkReturn
unsigned char*
CUserAllocator::XAlloc(
	__in size_t size
	)
{
	return static_cast<unsigned char*>(
		reinterpret_cast<decltype(&VirtualAlloc)>(m_allocx)(
			nullptr,
			size,
			MEM_COMMIT,
			PAGE_EXECUTE_READWRITE));
}
