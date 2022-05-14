#include "includes.h"

DWORD WINAPI TriggerBotThread(HMODULE hMod) {
	while (!GetAsyncKeyState(VK_END)) {
		LocalPlayer L;
		Entity E;

		if (L.Exists() && Settings.enableTriggerBot) {
			int localTeam = L.GetTeam();
			int localHealth = L.GetHealth();
			int CrosshairID = L.CrosshairID();

			if (CrosshairID > 0 && CrosshairID < 64) {
				DWORD entity = E.GetEntity(CrosshairID - 1);
				int entityTeam = E.GetEntityTeam(entity);
				int entityHealth = E.GetEntityHp(entity);
				
				if (localTeam != entityTeam) {
					if (entityHealth > 0 && entityHealth <= 100) {
						if (localHealth > 0) {
							L.ForceAttack();
							Sleep(20);
							L.StopAttack();
						}
					}
				}
			}
		}
		Sleep(1);
	}
	FreeLibraryAndExitThread(hMod, 0);
}