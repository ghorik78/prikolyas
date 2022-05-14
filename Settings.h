#include "includes.h"

class UserSettings {
public:
	//VISUALS
	bool enableWH = false;
	bool enableWH_team = false;

	int enemyColorR = 255;
	int enemyColorG = 0;
	int enemyColorB = 0;
	
	//RGB -> RGB/255
	int teammateColorR = 10;
	int teammateColorG = 10;
	int teammateColorB = 255;

	//AIMBOT
	bool enableAimBot = false;
	bool enableTriggerBot = false;
	bool enableTriggerBotV2 = false;

	float smooth = 0.01f;

	int aimFOV = 360;

	//MISC
	bool enableBunnyHop = false;
	bool enableRadarHack = false;
	bool enableRCS = false;
	bool enableNoFlash = false;
	bool enableThirdPerson = false;
};