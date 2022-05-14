#include "includes.h"

class LocalPlayer {
public:
	DWORD GetLocalPlayer();

	bool Exists();

	void ForceJump();

	int GetHealth();
	int GetTeam();
	int CrosshairID();

	void ForceAttack();
	void StopAttack();
	void SetViewAngles(Vector3 input);

	Vector3 GetViewAngles();
	Vector3 GetLocation();
	Vector3 GetBonePosition(int bone);
	Vector2 GetBonePositionScreen(int bone);
};