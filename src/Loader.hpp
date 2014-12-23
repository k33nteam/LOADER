#pragma once

#include <sal.h>

#include <Common/internals/Image.h>
#include "ExecAllocator.h"
#include "user/Allocator.h"
#include "kernel/Allocator.h"
#include "DynamicClass.h"

class CLoader
{
	unsigned char* m_newModuleBase;

	CLoader(
		__in IExecAllocator& allocator,
		__in const void* nt,
		__in CImage& module
		) :
		m_newModuleBase(allocator.XAlloc(module.SizeOfImage()))
	{
		if (!m_newModuleBase)
			return;

		module.Rellocate(m_newModuleBase);
	}

public:
	static
	CLoader*
	UserLoader(
		__in const void* ntdll,
		__in const void* module
		)
	{
		CImage main_img(module);
		CUserAllocator allocator(ntdll);
		return new CLoader(allocator, ntdll, main_img);
	}

	static
	CLoader*
	KernelLoader(
		__in const void* ntoskrnl,
		__in const void* module
		)
	{
		CImage main_img(module);
		CKernelAllocator allocator(ntoskrnl);
		return new CLoader(allocator, ntoskrnl, main_img);
	}	

	template<typename PROCEDURE_T>
	__checkReturn
	PROCEDURE_T
	GetProc(
		__in const char* procName
		)
	{
		CImage img(m_newModuleBase);
		return reinterpret_cast<PROCEDURE_T>(img.GetProcAddress(procName));
	}
};
