#include "includes.h"

DWORD WINAPI NoFlashThread(HMODULE hMod) {
	GameEngine E;
	LocalPlayer L;
	while (!GetAsyncKeyState(VK_END)) {
		if (L.Exists() && Settings.enableNoFlash) {
			Sleep(5);
			*(FLOAT*)(L.GetLocalPlayer() + m_flFlashDuration) = 0.0f;
		}
		Sleep(3);
	}
	FreeLibraryAndExitThread(hMod, 0);
}