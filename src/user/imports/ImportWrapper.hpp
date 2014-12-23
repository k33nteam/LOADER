#pragma once

#include <windows.h>
#include <Common/user/Externs.h>

#pragma pack(push, 1)
extern "C"
{
	decltype(&_vsnprintf) Ex_vsnprintf;
	decltype(&RtlUnicodeToMultiByteN) Ex_RtlUnicodeToMultiByteN;
	decltype(&RtlRaiseException) Ex_RtlRaiseException;
	decltype(&OutputDebugStringA) Ex_OutputDebugStringA;
	decltype(&HeapReAlloc) Ex_HeapReAlloc;
	decltype(&HeapFree) Ex_HeapFree;
	decltype(&HeapAlloc) Ex_HeapAlloc;
	decltype(&GetProcessHeap) Ex_GetProcessHeap;
	decltype(&GetModuleHandleW) Ex_GetModuleHandleW;
	decltype(&GetCommandLineW) Ex_GetCommandLineW;
	decltype(&_strnicmp) Ex_strnicmp;
}
#pragma pack(pop)

