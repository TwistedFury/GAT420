#include "framework.h"
#include <iostream>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::cout << "DLL Loaded.\n";
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        std::cout << "DLL Unloaded.\n";
        break;
    }
    return TRUE;
}

