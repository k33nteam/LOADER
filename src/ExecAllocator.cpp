#include "ExecAllocator.h"
#include <Common/utils/GlobalDllProxy.h>

CExecAllocator::CExecAllocator(
	__in const void* kernel,
	__in const char* alloc,
	__in const char* free)
{
	m_allocx = GlobalDllProxy::GetProcAddr(kernel, alloc);
	m_freex = GlobalDllProxy::GetProcAddr(kernel, free);
}
