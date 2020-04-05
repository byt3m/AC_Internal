#include "stdafx.h"
#pragma comment(lib,"OpenGL32.lib")

#include <windows.h>
#include <gl\gl.h>
#include "gltext.h"
#include "glDraw.h"
#include "mem.h"
//https://guidedhacking.com/

GL::Font glFont;
#define MENU_FONT_HEIGHT 15

void HackLoop()
{
	HDC currentHDC = wglGetCurrentDC();

	if (!glFont.bBuilt || currentHDC != glFont.hdc)
	{
		glFont.Build(MENU_FONT_HEIGHT);
	}

	GL::SetupOrtho();
	//Draw here
	GL::RestoreGL();
}

GL::twglSwapBuffers owglSwapBuffers;

BOOL __stdcall hwglSwapBuffers(HDC hDc)
{
	HackLoop();
	return owglSwapBuffers(hDc);
}

DWORD WINAPI dwMainThread(LPVOID)
{
	GL::Hook("wglSwapBuffers", (uintptr_t &)owglSwapBuffers, &hwglSwapBuffers);
	return TRUE;
}

BOOL __stdcall DllMain(HINSTANCE hModule, uintptr_t  dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, dwMainThread, 0, 0, 0);
	default:
		break;
	}
	return TRUE;
}