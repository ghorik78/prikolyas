#include "includes.h"

void LocalPlayer::SetViewAngles(Vector3 input) {
	GameEngine E;
	input.Normalize();
	Vector3* ViewAngles = (Vector3*)(*(DWORD*)(E.engineBase() + dwClientState) + dwClientState_ViewAngles);
	*ViewAngles = input;
}

Vector3 LocalPlayer::GetViewAngles() {
	GameEngine E;
	Vector3* ViewAngles = (Vector3*)(*(DWORD*)(E.engineBase() + dwClientState) + dwClientState_ViewAngles);
	return *ViewAngles;
}

Vector3 LocalPlayer::GetLocation() {
	DWORD player = GetLocalPlayer();
	if (player) {
		return *(Vector3*)(player + m_vecOrigin);
	}
	else return { 0, 0, 0 };
}

//Vector3 LocalPlayer::GetBonePosition(int bone) {
//	DWORD player = GetLocalPlayer();
//	if (player) {
//		uintptr_t BoneMatrixBased = *(uintptr_t*)(player + m_dwBoneMatrix);
//		BoneMatrix targetBone = *(BoneMatrix*)(BoneMatrixBased + sizeof(bone) * bone);
//		Vector3 Location = { targetBone.x, targetBone.y, targetBone.z };
//		return Location;
//	}
//	return { 0, 0, 0 };
//}
//
//Vector2 LocalPlayer::GetBonePositionScreen(int bone) {
//	GameEngine E;
//	DWORD player = GetLocalPlayer();
//	if (player) {
//		uintptr_t BoneMatrixBased = *(uintptr_t*)(player + m_dwBoneMatrix);
//		BoneMatrix targetBone = *(BoneMatrix*)(BoneMatrixBased + sizeof(bone) * bone);
//		Vector3 Location = { targetBone.x, targetBone.y, targetBone.z };
//		
//		float Matrix[16];
//		Vector2 OutVec;
//		memcpy(&Matrix, (PBYTE*)(E.moduleBase() + dwViewMatrix), sizeof(Matrix));
//
//		if (WorldToScreen(Location, OutVec, Matrix)) {
//			return OutVec;
//		}
//	}
//	return { 0, 0};
//}

DWORD LocalPlayer::GetLocalPlayer() {
	GameEngine E;
	return *(DWORD*)(E.moduleBase() + dwLocalPlayer);
}

bool LocalPlayer::Exists() {
	GameEngine E;
	if (*(DWORD*)(E.moduleBase() + dwLocalPlayer)) return true;
	else return false;
}

void LocalPlayer::ForceJump() {
	GameEngine E;
	*(DWORD*)(E.moduleBase() + dwForceJump) = 6;
}

int LocalPlayer::GetHealth() {
	DWORD player = GetLocalPlayer();
	if (player) return *(int*)(player + m_iHealth);
	else return -1;
}

int LocalPlayer::GetTeam() {
	DWORD player = GetLocalPlayer();
	if (player) return *(int*)(player + m_iTeamNum);
	return -1;
}

int LocalPlayer::CrosshairID() {
	DWORD player = GetLocalPlayer();
	if (player) return *(int*)(player + m_iCrosshairId);
	else return -1;
}

void LocalPlayer::ForceAttack() {
	GameEngine E;
	*(int*)(E.moduleBase() + dwForceAttack) = 5;
}

void LocalPlayer::StopAttack() {
	GameEngine E;
	*(int*)(E.moduleBase() + dwForceAttack) = 4;
}

