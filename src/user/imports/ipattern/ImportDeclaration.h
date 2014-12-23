#pragma once

#include "../../Resolver.h"
#include "ImportWrapper.hpp"

static
const
void** const g_pUserModeImports = reinterpret_cast<const void** const>(0);

static
const char* const g_pUserModeModules[] =
{
	""
};

static
const char* const g_pUserModeProcedures[] =
{
	""
};

static
const IMPORT_TABLE const g_UserModeImportsInfo[1] =
{
	{0,0,0}
};

