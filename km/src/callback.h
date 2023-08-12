#pragma once

#include "memory/memory.h"

#define key_val 69420

#define print(x, ...) DbgPrintEx(0, 0, x, __VA_ARGS__)

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
	uintptr_t key;
	uintptr_t request;
	uintptr_t address;
	uintptr_t PID;
	const char* processName;
	const char* moduleName;
	void* pBuffer;
	uintptr_t size_of_buffer;
};


namespace callback
{

	inline EX_CALLBACK_FUNCTION registry;
	inline LARGE_INTEGER cookie;
	inline PEPROCESS um;
	NTSTATUS init();
}