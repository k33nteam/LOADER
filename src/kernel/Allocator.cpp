#include "Allocator.h"

#include <ntifs.h>

CKernelAllocator::CKernelAllocator(
	__in const void* kernel
	) : CExecAllocator(kernel, "ExAllocatePoolWithTag", "ExFreePoolWithTag")
{
}

void
CKernelAllocator::XFree(
	__inout unsigned char* execMem
	)
{
	reinterpret_cast<decltype(&ExFreePoolWithTag)>(m_freex)(
		execMem, 
		'EXEC');
}

__checkReturn
unsigned char*
CKernelAllocator::XAlloc(
	__in size_t size
	)
{
	return static_cast<unsigned char*>(
		reinterpret_cast<decltype(&ExAllocatePoolWithTag)>(m_allocx)(
			NonPagedPoolExecute,
			size,
			'EXEC'));
}
