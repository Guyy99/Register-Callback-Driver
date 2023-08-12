#pragma once

#include <windows.h>

#define key_val 69420

enum requests
{
	REQUEST_PEB,
	REQUEST_PID,
	REQUEST_MODULEBASE,
	REQUEST_READ,
	REQUEST_WRITE
};

struct KM_REQ
{
	uintptr_t key = key_val;
	uintptr_t request;
	uintptr_t address;
	uintptr_t PID;
	const char* processName;
	const char* moduleName;
	void* pBuffer;
	uintptr_t size_of_buffer;
};

class driver
{
private:

	HKEY reg_key;
	LPCWSTR reg_key_name = (LPCWSTR)"km_req";

	KM_REQ instructions;

	void make_request()
	{
		RegSetValueExW(reg_key, reg_key_name, 0, REG_QWORD, (const BYTE*)&instructions, sizeof(uintptr_t));
	}

public:

	driver()
	{
		LSTATUS status = RegOpenKeyW(HKEY_LOCAL_MACHINE, reg_key_name, &reg_key);
		if (status != ERROR_SUCCESS)
		{
			RegCreateKeyA(HKEY_LOCAL_MACHINE, (LPCSTR)reg_key_name, &reg_key);
		}

		RegSetValueExW(reg_key, reg_key_name, 0, REG_QWORD, (const BYTE*)GetCurrentProcessId(), sizeof(uintptr_t));
	}

	~driver()
	{
		RegCloseKey(reg_key);
	}

	uintptr_t procID(const char* process)
	{
		instructions.request = REQUEST_PID;
		instructions.processName = process;

		make_request();

		return instructions.PID;
	}

};
