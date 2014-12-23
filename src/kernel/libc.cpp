#include <ntifs.h>

#include "KernelModule.hpp"
#include "Resolver.cpp"

//---------------------------
//------   INSTALL   --------
//---------------------------
extern "C"
__declspec(dllexport)
NTSTATUS
NTAPI
DriverEntry(
	__in DRIVER_OBJECT* driverObject,
	__in void* param
	)
{
	DbgBreakPoint();
	if (!Resolver::ResolveKernelEntry())
		return STATUS_UNSUCCESSFUL;

	driverObject->DriverUnload = reinterpret_cast<DRIVER_UNLOAD*>(Resolver::ExitKernelEntry);

	CKernelModule::GetInstance().SetParams(driverObject, param);

	if (main())
		return STATUS_SUCCESS;

	return STATUS_UNSUCCESSFUL;
}
