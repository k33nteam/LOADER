#pragma once

#include <windows.h>
#include "../Module.hpp"

class CExeModule
{
public:
	static
	CModule&
	GetInstance()
	{
		return CModule::GetInstance();
	}

	static
	void*
	ModuleBase()
	{
		return CModule::GetInstance().m_module;
	}

	static
	const WCHAR*
	CommandLine()
	{
		return static_cast<const WCHAR*>(CModule::GetInstance().m_param);
	}
};

class CDllModule
{
public:
	static
	CModule&
	GetInstance()
	{
		return CModule::GetInstance();
	}

	static
	void*
	ModuleBase()
	{
		return CModule::GetInstance().m_module;
	}
};
