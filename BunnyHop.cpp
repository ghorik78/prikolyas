#include "includes.h"

DWORD WINAPI BunnyHopThread(HMODULE hMod) {
	while (!GetAsyncKeyState(VK_END)) {
		//глобал -> локал ??
		LocalPlayer L;

		if (Settings.enableBunnyHop) {
			DWORD flag = *(BYTE*)(L.GetLocalPlayer() + m_fFlags);

			if (GetAsyncKeyState(VK_SPACE) && (flag & (1 << 0))) {
				L.ForceJump();
			}
		}
		Sleep(1);
	}
	FreeLibraryAndExitThread(hMod, 0);
}