
#pragma once

#include "ImportWrapper.hpp"
#include "../../Resolver.h"

static
const
void** const g_pUserModeImports = reinterpret_cast<const void** const>(&Ex_vsnprintf);

static
const char* const g_pUserModeModules[] =
{
	"msvcrt.dll",
	"ntdll.dll",
	"ntdll.dll",
	"kernel32.dll",
	"kernel32.dll",
	"kernel32.dll",
	"kernel32.dll",
	"kernel32.dll",
	"kernel32.dll",
	"kernel32.dll",
	"ntdll.dll",
};

static
const char* const g_pUserModeProcedures[] =
{
	"_vsnprintf",
	"RtlUnicodeToMultiByteN",
	"RtlRaiseException",
	"OutputDebugStringA",
	"HeapReAlloc",
	"HeapFree",
	"HeapAlloc",
	"GetProcessHeap",
	"GetModuleHandleW",
	"GetCommandLineW",
	"_strnicmp",
};

static
const IMPORT_TABLE const g_UserModeImportsInfo[11] =
{
	{ &g_pUserModeModules[0x000], &g_pUserModeProcedures[0x000], reinterpret_cast<const void**>(&Ex_vsnprintf) },
	{ &g_pUserModeModules[0x001], &g_pUserModeProcedures[0x001], reinterpret_cast<const void**>(&Ex_RtlUnicodeToMultiByteN) },
	{ &g_pUserModeModules[0x002], &g_pUserModeProcedures[0x002], reinterpret_cast<const void**>(&Ex_RtlRaiseException) },
	{ &g_pUserModeModules[0x003], &g_pUserModeProcedures[0x003], reinterpret_cast<const void**>(&Ex_OutputDebugStringA) },
	{ &g_pUserModeModules[0x004], &g_pUserModeProcedures[0x004], reinterpret_cast<const void**>(&Ex_HeapReAlloc) },
	{ &g_pUserModeModules[0x005], &g_pUserModeProcedures[0x005], reinterpret_cast<const void**>(&Ex_HeapFree) },
	{ &g_pUserModeModules[0x006], &g_pUserModeProcedures[0x006], reinterpret_cast<const void**>(&Ex_HeapAlloc) },
	{ &g_pUserModeModules[0x007], &g_pUserModeProcedures[0x007], reinterpret_cast<const void**>(&Ex_GetProcessHeap) },
	{ &g_pUserModeModules[0x008], &g_pUserModeProcedures[0x008], reinterpret_cast<const void**>(&Ex_GetModuleHandleW) },
	{ &g_pUserModeModules[0x009], &g_pUserModeProcedures[0x009], reinterpret_cast<const void**>(&Ex_GetCommandLineW) },
	{ &g_pUserModeModules[0x00a], &g_pUserModeProcedures[0x00a], reinterpret_cast<const void**>(&Ex_strnicmp) },
};

