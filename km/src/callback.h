#pragma once

#include "memory/memory.h"

inline const char* k = "__guyy__ on dc";
inline ANSI_STRING AS = { 0 };
inline UNICODE_STRING key = { 0 };

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

	inline EX_CALLBACK_FUNCTION registry; // callback function
	inline LARGE_INTEGER cookie;
	NTSTATUS init();
}	