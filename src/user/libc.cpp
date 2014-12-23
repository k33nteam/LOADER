#include <windows.h>

#include "UserModule.hpp"
#include "Resolver.cpp"

#include <Common/internals/Image.h>

#ifdef DLL

#include <loader/src/DynamicClass.h>
#include <Common/utils/ScopedThread.hpp>

class CExitThread :
	public CScopedThread,
	public IExitCallback
{
	DWORD
	Main() override
	{
		return main();
	};
};


extern "C"
_declspec(dllexport)
BOOL 
WINAPI
DllMain(
	__in HMODULE hModule,
	__in DWORD reason,
	__in LPVOID lpReserved
	)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		{
			if (!Resolver::ResolveUserEntry())
				return FALSE;

			CDllModule::GetInstance().SetParams(hModule, nullptr);

			auto main_thread = new CExitThread();
			if (!main_thread)
				return false;
			
			CDllModule::GetInstance().RegisterRuntimeClass(*main_thread);
			return TRUE;
		}
	case DLL_PROCESS_DETACH:
	{
			Resolver::ExitUserEntry();
			return TRUE;
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

#else

extern "C"
_declspec(dllexport)
void
WINAPI
Main()
{
	if (!Resolver::ResolveUserEntry())
		return;

	CExeModule::GetInstance().SetParams(GetModuleHandle(nullptr), GetCommandLineW());

	(void)main();

	Resolver::ExitUserEntry();
}

#endif
