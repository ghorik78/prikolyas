#include "includes.h"

DWORD Entity::GetEntity(int index) {
	GameEngine E;
	return *(DWORD*)(E.moduleBase() + dwEntityList + (index * 0x10));
}

int Entity::GetEntityHp(DWORD entity) {
	return *(int*)(entity + m_iHealth);
}

int Entity::GetEntityTeam(DWORD entity) {
	return *(int*)(entity + m_iTeamNum);
}

//не трогать
//Vector3 Entity::GetBonePosition(DWORD entity, int bone) {
//	DWORD ENT = GetEntity(entity);
//	if (ENT) {
//		uintptr_t BoneMatrixBased = *(uintptr_t*)(ENT + m_dwBoneMatrix);
//		BoneMatrix targetBone = *(BoneMatrix*)(BoneMatrixBased + sizeof(bone) * bone);
//		Vector3 Location = { targetBone.x, targetBone.y, targetBone.z };
//		return Location;
//	}
//	return { 0, 0, 0 };
//}
//
//Vector2 Entity::GetBonePositionScreen(DWORD entity, int bone) {
//	GameEngine E;
//	DWORD ENT = GetEntity(entity);
//	if (ENT) {
//		uintptr_t BoneMatrixBased = *(uintptr_t*)(ENT + m_dwBoneMatrix);
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
//	return { 0, 0 };
//}