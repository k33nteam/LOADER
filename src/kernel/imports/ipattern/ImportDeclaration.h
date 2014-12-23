#pragma once

#include <Common/kernel/Externs.h>

#include "ImportWrapper.hpp"
#include "../../Resolver.h"

static
const
void** const g_pKernelModeImports = reinterpret_cast<const void** const>(0);

static
const char* const g_pKernelModeModules[] =
{
	""
};

static
const char* const g_pKernelModeProcedures[] =
{
	""
};

static
const IMPORT_TABLE const g_KernelModeImportsInfo[1] =
{
	{0,0,0}
};

