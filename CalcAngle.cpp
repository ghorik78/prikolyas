#include "includes.h"

Vector3 CalcAngle(Vector3 src, Vector3 dst) {
	Vector3 angle, e = { dst.x - src.x, dst.y - src.y, dst.z - src.z };
	double eh = sqrt(e.x * e.x + e.y * e.y);
	angle.x = atan2(-e.z, eh) * 180 / 3.14159f;
	angle.y = atan2(e.y, e.x) * 180 / 3.14159f;
	angle.z = 0;
	return angle;
}