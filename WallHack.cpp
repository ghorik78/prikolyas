#include "includes.h"

DWORD WINAPI WallHackThread(HMODULE hMod) {
	while (true) {
		GameEngine E;
		LocalPlayer L;

		DWORD dwEntity, glowManager;
		int localTeam, entityTeam, entityGlow;

		if (L.Exists() && Settings.enableWH) {
			glowManager = *(DWORD*)(E.moduleBase() + dwGlowObjectManager);
			localTeam = *(DWORD*)(L.GetLocalPlayer() + m_iTeamNum);

			for (int i = 0; i < 32; i++) {
				dwEntity = *(DWORD*)(E.moduleBase() + dwEntityList + i * 0x10);

				if (dwEntity) {
					entityTeam = *(INT*)(dwEntity + m_iTeamNum);
					entityGlow = *(INT*)(dwEntity + m_iGlowIndex);

					if (localTeam != entityTeam) {
						*(FLOAT*)(glowManager + (entityGlow * 0x38) + 0x8) = Settings.enemyColorR;
						*(FLOAT*)(glowManager + (entityGlow * 0x38) + 0xC) = Settings.enemyColorG;
						*(FLOAT*)(glowManager + (entityGlow * 0x38) + 0x10) = Settings.enemyColorB;
						*(FLOAT*)(glowManager + (entityGlow * 0x38) + 0x14) = 255;
						*(INT*)(glowManager + (entityGlow * 0x38) + 0x28) = 1;
					}

					if (localTeam == entityTeam && Settings.enableWH_team) {
						*(FLOAT*)(glowManager + (entityGlow * 0x38) + 0x8) = Settings.teammateColorR;
						*(FLOAT*)(glowManager + (entityGlow * 0x38) + 0xC) = Settings.teammateColorG;
						*(FLOAT*)(glowManager + (entityGlow * 0x38) + 0x10) = Settings.teammateColorB;
						*(FLOAT*)(glowManager + (entityGlow * 0x38) + 0x14) = 255;
						*(INT*)(glowManager + (entityGlow * 0x38) + 0x28) = 1;
					}
				}
			}
		}
		Sleep(1);
	}
	FreeLibraryAndExitThread(hMod, 0);
}