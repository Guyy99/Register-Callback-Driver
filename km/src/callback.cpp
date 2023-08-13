#include "callback.h"

#pragma warning (disable : 4100)

NTSTATUS callback::init()
{
    RtlInitAnsiString(&AS, k);
    RtlAnsiStringToUnicodeString(&key, &AS, true); // changes const char* to unicode string

    NTSTATUS status = CmRegisterCallback(callback::registry, NULL, &cookie); // registers callback

    if (status != STATUS_SUCCESS)
    {
        print("registry::init_callback() -> failed: CmRegisterCallback Failed");
        return STATUS_FATAL_APP_EXIT;
    }

    print("registry::init_callback() -> succces: Created Registry Callback");

    return STATUS_SUCCESS;
}

// Registry callback function, called every time a registry key is modified/created/deleted etc

_Use_decl_annotations_
NTSTATUS
callback::registry(
    PVOID  CallbackContext,
    PVOID  Argument1,
    PVOID  Argument2
)
{
    if (Argument1 != (PVOID)RegNtSetValueKey) // checks to make sure that its a key value change
        return STATUS_SUCCESS;

    REG_SET_VALUE_KEY_INFORMATION* preInfo = (REG_SET_VALUE_KEY_INFORMATION*)Argument2;

    
    if (RtlEqualUnicodeString(preInfo->ValueName, &key, TRUE) == 0) // checks if registry key name is equal to our key
        return STATUS_SUCCESS;
    
    KM_REQ* request = *(KM_REQ**)preInfo->Data;

    if (!request) return STATUS_SUCCESS;

    print("got the cheeky request pointer");

    // handle requests here

    if (request->request == REQUEST_PID)
    {
        request->PID = (uintptr_t)memory::get_process_id(request->processName);
    }

   
   
    return STATUS_SUCCESS;
}