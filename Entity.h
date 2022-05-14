#include "includes.h"

class Entity {
public:
	DWORD GetEntity(int index);

	int GetEntityHp(DWORD entity);
	int GetEntityTeam(DWORD entity);

	Vector3 GetBonePosition(DWORD entity, int bone);
	Vector2 GetBonePositionScreen(DWORD entity, int bone);
};