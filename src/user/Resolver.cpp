#include <sal.h>
#include <windows.h>
#include <winternl.h>

#include <libc/src/libc.h>
#include <libc/src/heap.h>
#include <libc/src/cpp.h>

#include <Common/utils/GlobalDllProxy.h>

#include "../Resolver.h"
#include "imports/ImportDeclaration.h"

#define TEST_MODE

namespace Resolver
{
	void
	SetUserLibc()
	{
		if (!gCrtHeap)
			gCrtHeap = GetProcessHeap();

		set_imports(UserMalloc, UserFree, UserRealloc, UserVsnPrintf, UserPrint);
	}
	
	__checkReturn
	bool
	ResolveUserImports()
	{
#if defined(_WIN64)
		PEB* peb = reinterpret_cast<PEB*>(__readgsqword(0x60));
#else
		PEB* peb = reinterpret_cast<PEB*>(__readfsdword(0x30));
#endif
		if (!peb)
			return false;

		if (!peb->Ldr)
			return false;

		if (!peb->Ldr->InMemoryOrderModuleList.Flink)
			return false;

		if (!peb->Ldr->InMemoryOrderModuleList.Flink->Flink)
			return false;

		if (!peb->Ldr->InMemoryOrderModuleList.Flink->Flink->Flink)
			return false;

		auto kernel32 = CONTAINING_RECORD(peb->Ldr->InMemoryOrderModuleList.Flink->Flink->Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
		if (!kernel32->DllBase)
			return false;

		const void* load_lib_a = GlobalDllProxy::GetProcAddr(kernel32->DllBase, "LoadLibraryA");
		if (!load_lib_a)
			return false;

		for (size_t i = 0; i < _countof(g_UserModeImportsInfo); i++)
		{
			const void* addr = GlobalDllProxy::ResolveProcAddress(
				reinterpret_cast<const decltype(&LoadLibraryA)>(load_lib_a),
				*g_UserModeImportsInfo[i].Module,
				*g_UserModeImportsInfo[i].ProcName);


			//so something not resolved, pobably fault of .py script ...
			if (!addr)
#ifdef TEST_MODE
			{
				SetUserLibc();
				printf("\n UNRESOLVED EXTERNAL SYMBOLS : %s.%s \n", *g_UserModeImportsInfo[i].Module, *g_UserModeImportsInfo[i].ProcName);
			}
#else
			return false;
#endif

			*g_UserModeImportsInfo[i].ExProc = addr;
		}
		return true;
	}

	__checkReturn
	bool
	ResolveUserEntry()
	{
		if (!ResolveUserImports())
			return false;

		SetUserLibc();
		cc_init(0);
		return true;
	}

	void
	ExitUserEntry()
	{
		cc_doexit(0, 0, 0);//call dtors
	}
}
