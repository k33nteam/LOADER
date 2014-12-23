#include <sal.h>
#include <ntifs.h>
#include <stdlib.h>
#include <intrin.h>
#include <minwindef.h>

#include <libc/src/libc.h>
#include <libc/src/pool.h>
#include <libc/src/cpp.h>

#include <Common/utils/GlobalDllProxy.h>
#include <Common/internals/QuerySystemInfo.hpp>

#include "../Resolver.h"
#include "imports/ImportDeclaration.h"

extern
void
set_imports(
	__in decltype(&malloc) cc_alloc,
	__in decltype(&free) cc_free,
	__in decltype(&realloc) cc_realloc,
	__in decltype(&vsnprintf_wrap) cc_vsnprintf,
	__in print_t cc_print
	);


#define QURY_SYSTEM_INFO_ALIAS ExZwQuerySystemInformation

extern "C"
decltype(&ZwQuerySystemInformation) QURY_SYSTEM_INFO_ALIAS;

struct NTINFO
{
	unsigned int NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Ntoskrnl;
};

#ifdef WIN64
static const size_t IA64_SYSENTER_EIP = 0xC0000082;
#else 
static const size_t IA64_SYSENTER_EIP = 0x176;
#endif

#define MZ_MAGIC 0x00905a4d

#define TEST_MODE

namespace Resolver
{
	void
	SetKernelLibc()
	{
		set_imports(PoolAlloc, PoolFree, PoolReAlloc, PoolVsnPrintf, PoolPrint);
	}

	__checkReturn
	HMODULE
	GetNtoskrnlBase()
	{
		NTINFO nt;
		bool query = CSystemInfo<NTINFO>::QuerInfo(SYSTEM_INFORMATION_CLASS_EX::SystemModuleInformation,
			&nt,
			sizeof(nt));

		if (!query)
			return nullptr;
		return static_cast<HMODULE>(nt.Ntoskrnl.ImageBase);
	}

	__checkReturn
	HMODULE
	NTAPI
	GetDriverBase(
		__in const char* sysName
		)
	{
		if (!stricmp("ntoskrnl.exe", sysName))
			return GetNtoskrnlBase();

		CSystemInfo<RTL_PROCESS_MODULES> sinfo(SYSTEM_INFORMATION_CLASS_EX::SystemModuleInformation);
		if (!sinfo.get())
			return nullptr;

		for (size_t i = 0; i < sinfo->NumberOfModules; i++)
			if (!stricmp(sysName, sinfo->Modules[i].FullPathName + sinfo->Modules[i].OffsetToFileName))
				return static_cast<HMODULE>(sinfo->Modules[i].ImageBase);

		return nullptr;
	}

	__checkReturn
	bool
	ResolveKernelImports()
	{
		//is already resolved ?
		if (QURY_SYSTEM_INFO_ALIAS)
			return true;

		const DWORD* ntoskrnl = reinterpret_cast<const DWORD*>(__readmsr(IA64_SYSENTER_EIP) & (~(PAGE_SIZE - 1)));
		while (MZ_MAGIC != ntoskrnl[0])
			ntoskrnl -= (PAGE_SIZE >> 2);

		const void* nt_query_info = GlobalDllProxy::GetProcAddr(ntoskrnl, "ZwQuerySystemInformation");
		if (!nt_query_info)
			return false;

		QURY_SYSTEM_INFO_ALIAS = reinterpret_cast<decltype(&ZwQuerySystemInformation)>(nt_query_info);

		for (size_t i = 0; i < _countof(g_KernelModeImportsInfo); i++)
		{
			const void* addr = GlobalDllProxy::ResolveProcAddress(
				GetDriverBase,
				*g_KernelModeImportsInfo[i].Module,
				*g_KernelModeImportsInfo[i].ProcName);

			//so something not resolved, pobably fault of .py script ...
			if (!addr)
#ifdef TEST_MODE
			{
				SetKernelLibc();
				DbgPrint("\n UNRESOLVED EXTERNAL SYMBOLS : %s.%s \n", *g_KernelModeImportsInfo[i].Module, *g_KernelModeImportsInfo[i].ProcName);
			}
#else
				return false;
#endif

			*g_KernelModeImportsInfo[i].ExProc = addr;
		}

		return true;
	}

	__checkReturn
	bool
	ResolveKernelEntry()
	{
		if (!ResolveKernelImports())
			return false;

		SetKernelLibc();
		cc_init(0);
		return true;
	}

	void
	NTAPI
	ExitKernelEntry(
		__in struct DRIVER_OBJECT*
		)
	{
		cc_doexit(0, 0, 0);//call dtors
	}
};
