#pragma comment(lib,"OpenGL32.lib")

#include <windows.h>
#include <gl\gl.h>
#include <iostream>
#include <fstream>

#include "gltext.h"
#include "glDraw.h"
#include "mem.h"

#include "Reclass.h"
#include "calcs.h"
#include "ESP.h"


HINSTANCE ghModule;
FILE* pFile = nullptr;
GL::twglSwapBuffers owglSwapBuffers;
BOOL isUnhooked = false;


BOOL __stdcall hwglSwapBuffers(HDC hDc)
{
    HDC currentHDC = wglGetCurrentDC();

    if (!glFont.bBuilt || currentHDC != glFont.hdc)
    {
        glFont.Build(10);
    }

    localPlayer->Health = 1000;
    localPlayer->PistolAmmo1 = 1000;
    localPlayer->RifleAmmo1 = 1000;
    localPlayer->GrenadeAmmo = 1000;
    localPlayer->GrenadeWaitTime = 0;

    GL::SetupOrtho();
    DrawESP();
    GL::RestoreGL();


    return owglSwapBuffers(hDc);
}


DWORD WINAPI dwMainThread(LPVOID)
{    
    /*AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);*/

    GL::Hook("wglSwapBuffers", (uintptr_t&)owglSwapBuffers, &hwglSwapBuffers);
    
    while (true)
    {
        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            mem::UnHook(5);
            isUnhooked = true;
        }

        if (GetAsyncKeyState(VK_END) & 1)
            if (isUnhooked)
                FreeLibraryAndExitThread(::ghModule, 0);
            else
                MessageBoxA(NULL, "Must unhook first!", "INFO", MB_OK);
    }

}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, dwMainThread, nullptr, 0, nullptr); //pointers arent 0
        DisableThreadLibraryCalls(hModule); //pass the actual module
        ::ghModule = hModule;
        //MessageBox(NULL, L"DLL ATTACHED", L"AssaultCube Internal", MB_OK);
        break;
    case DLL_PROCESS_DETACH:        
        /*fclose(pFile);
        FreeConsole();*/
        //MessageBox(NULL, L"DLL DETACHED", L"AssaultCube Internal", MB_OK);
        break;
    default:
        break;
    }
    return TRUE;
}