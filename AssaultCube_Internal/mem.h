#pragma once

#include "windows.h"
#include <vector>


namespace mem
{
	bool Hook(void * toHook, void * ourFunct, int len);
	void * TrampolineHook(void * toHook, void * ourFunct, int len);
	void UnHook(int len);
};