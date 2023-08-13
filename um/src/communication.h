#pragma once

#include <windows.h>

inline const char* key = "__guyy__ on dc";

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
	

	KM_REQ instructions;

	void make_request()
	{
		RegOpenKeyExA(HKEY_LOCAL_MACHINE, "", 0, KEY_ALL_ACCESS, &reg_key); // opens a registry key

		if (reg_key == NULL || reg_key == INVALID_HANDLE_VALUE) {
			return;
		}
		void* val = (void*)&instructions;

		RegSetValueExA(reg_key, key, 0, REG_QWORD, reinterpret_cast<BYTE*>(&val), sizeof(uint64_t)); // writes a pointer to our instructions in that registry key, with our key as the name
	}

public:

	driver() {}

	// modify request values here to return different values from kernel

	uintptr_t procID(const char* process)
	{
		instructions.request = REQUEST_PID;
		instructions.processName = process;

		make_request();

		return instructions.PID;
	}

};
