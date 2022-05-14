#include "includes.h"

struct Vector2 {
	float x, y;
};

struct Vector3 {
	float x, y, z;

	Vector3 operator+(Vector3 S) {
		return { x + S.x, y + S.y, z + S.z };
	}
	Vector3 operator-(Vector3 S) {
		return { x - S.x, y - S.y, z - S.z };
	}
	Vector3 operator*(float S) {
		return { x * S, y * S, z * S };
	}
	Vector3 operator/(float S) {
		return { x / S, y / S, z / S };
	}

	void Normalize() {
		if (y < -180) y += 360;
		if (y > 180) y -= 360;
		if (x < -89) x += 180;
		if (x > 89) x -= 180;
		z = 0;
	}
};

struct Vector4 {
	float x, y, z, w;
};