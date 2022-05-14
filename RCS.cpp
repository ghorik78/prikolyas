#include "includes.h"

DWORD WINAPI RCSThread(HMODULE hMod) {
	//óòàùèòü â ãëîáàë
	LocalPlayer L;
	GameEngine E;
	Vector3 oldPunch{ 0, 0, 0 };
	while (!GetAsyncKeyState(VK_END)) {

		DWORD localPlayer = L.GetLocalPlayer(); //check that shit

		if (Settings.enableRCS) {
			if (localPlayer) {
				int* shotsFired = (int*)(localPlayer + m_iShotsFired);
				Vector3* RecoilPunch = (Vector3*)(localPlayer + m_aimPunchAngle);
				Vector3 PunchAngle = *RecoilPunch * 2.f;

				if (*shotsFired > 1 && GetAsyncKeyState(VK_LBUTTON)) {
					Vector3 Angle = L.GetViewAngles() + oldPunch - PunchAngle;
					L.SetViewAngles(Angle);
				}
				oldPunch = PunchAngle;
			}
			else {
				localPlayer = L.GetLocalPlayer();
			}
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}
