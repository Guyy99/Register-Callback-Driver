#include "callback.h"

#pragma warning (disable : 4100)

NTSTATUS callback::init()
{
    NTSTATUS status = CmRegisterCallback(callback::registry, NULL, &cookie);

    if (status != STATUS_SUCCESS)
    {
        print("registry::init_callback() -> failed: CmRegisterCallback Failed");
        return STATUS_FATAL_APP_EXIT;
    }

    print("registry::init_callback() -> succces: Created Registry Callback");

    return STATUS_SUCCESS;
}



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

    REG_POST_OPERATION_INFORMATION* postInfo = (REG_POST_OPERATION_INFORMATION*)Argument2;
    REG_SET_VALUE_KEY_INFORMATION* preInfo = (REG_SET_VALUE_KEY_INFORMATION*)postInfo->PreInformation;
    
    if (RtlEqualUnicodeString(preInfo->ValueName, &MyKey, TRUE) == 0)
        return STATUS_SUCCESS;

    if (preInfo->DataSize != sizeof(uintptr_t)) // checks data is a pointer
        return STATUS_SUCCESS;
    
    KM_REQ* request = *(KM_REQ**)preInfo->Data;

    if (!request) return STATUS_SUCCESS;

    if (request->key != key_val) return STATUS_SUCCESS;

    print("got the cheeky request pointer");

   
   
    return STATUS_SUCCESS;
}