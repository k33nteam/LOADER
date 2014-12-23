#pragma once

#include <sal.h>

bool
main();

struct IMPORT_TABLE
{
	const char*const* Module;
	const char*const* ProcName;
	const void** ExProc;
};

namespace Resolver
{
	__checkReturn
	bool
	ResolveUserEntry();

	void
	ExitUserEntry();

	__checkReturn
	bool
	ResolveKernelEntry();

	void
	NTAPI
	ExitKernelEntry(
		__in struct DRIVER_OBJECT*
		);
};
