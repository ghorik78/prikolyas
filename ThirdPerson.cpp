#include "includes.h"

DWORD WINAPI ThirdPersonThread(HMODULE hMod) {
	//�����->������ + ����� �������
	LocalPlayer L;
	while (!GetAsyncKeyState(VK_MENU)) {
		if (L.Exists() && Settings.enableThirdPerson) {
			*(INT*)(L.GetLocalPlayer() + m_iObserverMode) = 1;
		}
		else *(INT*)(L.GetLocalPlayer() + m_iObserverMode) = 0;
	}
	FreeLibraryAndExitThread(hMod, 0);
}