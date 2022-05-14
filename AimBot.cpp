#include "includes.h"

DWORD WINAPI AimBotThread(HMODULE hMod) {
	GameEngine E;
	LocalPlayer L;

	int screenX = GetSystemMetrics(SM_CXSCREEN);
	int screenY = GetSystemMetrics(SM_CYSCREEN);

	//kick Pifagora
	float closestEntity = 1000 * 1000;
	uintptr_t bestEntity = NULL;

	int entityHealth, localTeam, entTeam;

	while (!GetAsyncKeyState(VK_END)) {
		if (L.Exists() && Settings.enableAimBot) {
			uintptr_t localPlayer = L.GetLocalPlayer();
			Vector3* viewAngles = (Vector3*)(*(uintptr_t*)(E.engineBase() + dwClientState) + dwClientState_ViewAngles);

			for (int i = 0; i < 32; i++) {
				uintptr_t PotentialTarget = *(uintptr_t*)(E.moduleBase() + dwEntityList + (i * 0x10));

				if (PotentialTarget) {

					entityHealth = *(INT*)(PotentialTarget + m_iHealth);
					
					if (entityHealth <= 0) continue;
					Vector3 LocalHeadPos;
					Vector3 EntityHeadPos;

					try {
						uintptr_t EntityBoneMatrix = *(uintptr_t*)(PotentialTarget + m_dwBoneMatrix);
						BoneMatrix EntityBone = *(BoneMatrix*)(EntityBoneMatrix + (sizeof(EntityBone) * 8));
						EntityHeadPos = { EntityBone.x, EntityBone.y, EntityBone.z };
					}
					catch (const std::exception) {};

					try {
						uintptr_t LocalBoneMatrix = *(uintptr_t*)(localPlayer + m_dwBoneMatrix);
						BoneMatrix LocalBone = *(BoneMatrix*)(LocalBoneMatrix + (sizeof(LocalBone) * 8));
						LocalHeadPos = { LocalBone.x, LocalBone.y, LocalBone.z };
					}
					catch (const std::exception) {};

					Vector3 TempAngles = CalcAngle(LocalHeadPos, EntityHeadPos);

					Vector2 ScreenPos;
					float viewMatrix[16];
					memcpy(&viewMatrix, (PBYTE*)(E.moduleBase() + dwViewMatrix), sizeof(viewMatrix));

					if (WorldToScreen(EntityHeadPos, ScreenPos, viewMatrix, screenX, screenY)) {
						float dist = sqrt(powf((screenX / 2 - ScreenPos.x), 2) + powf((screenY / 2 - ScreenPos.y), 2));

						if (((bestEntity == PotentialTarget) || (dist < closestEntity)) && (dist < Settings.aimFOV)) {

							bestEntity = PotentialTarget;
							closestEntity = dist;

							if (GetAsyncKeyState(VK_MENU)) {
								localTeam = *(DWORD*)(localPlayer + m_iTeamNum);
								entTeam = *(DWORD*)(PotentialTarget + m_iTeamNum);

								bool isDormant = *(BOOL*)(bestEntity + m_bDormant);
								bool isSpotted = *(BOOL*)(bestEntity + m_bSpottedByMask);

								if ((localTeam != entTeam)) {
									Vector3* aimRecoilPunch = (Vector3*)(localPlayer + m_aimPunchAngle);
									Vector3 punchAngle = *aimRecoilPunch * 2;
									TempAngles = TempAngles - punchAngle;

									Vector3 CurrAngle = *viewAngles;
									Vector3 Delta = TempAngles - CurrAngle;
									Vector3 AimAngle = CurrAngle + Delta / (Settings.smooth * 500);
									AimAngle.Normalize();
									*viewAngles = AimAngle;


									int cID = L.CrosshairID();
									if (Settings.enableTriggerBotV2 && GetAsyncKeyState(VK_MENU) && cID > 0 && cID < 64) *(INT*)(E.moduleBase() + dwForceAttack) = 6;
								}
							}
						}
					}
				}
			}
		}
		Sleep(1);
	}
	FreeLibraryAndExitThread(hMod, 0);
}
