#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

uintptr_t FindDMAAddress(uintptr_t ptr, vector<unsigned int> offsets) {
    uintptr_t addr = ptr;

    for (unsigned int i = 0; i < offsets.size(); i++) {
        addr = *(uintptr_t*)addr;
        addr += offsets[i];
    }

    return addr;
}

DWORD WINAPI MainThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;

    freopen_s(&f, "CONOUT$", "w", stdout);

    printf("Wesnoth Internal Cheat Injected!");

    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(L"wesnoth.exe");

    vector<unsigned int> goldOffsets = { 0xc, 0x4, 0x4 };

    while (true) {
        if (GetAsyncKeyState(0x47)) { // 0x47 = G
            int* gold = (int*)FindDMAAddress(moduleBase + 0x01157320, goldOffsets);
            *gold = 5000;
        }
        Sleep(2000);
    }

    // Clear console
    FreeConsole();
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0));
    }
    return TRUE;
}

