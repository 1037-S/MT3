#include "Vector3Mas.h"
#include <Novice.h>
#include <cmath>

Vector3Mas::~Vector3Mas() {}

// 加算
Vector3 Vector3Mas::Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

 // 減算
Vector3 Vector3Mas::Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

// スカラー倍
Vector3 Vector3Mas::Multiply(float scalar, const Vector3& v) {
	Vector3 result = {};

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;
}
// 内積
float Vector3Mas::Dot(const Vector3& v1, const Vector3& v2) {
	float result = {};

	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}
// 長さ(ノルム)
float Vector3Mas::Length(const Vector3& v) {
	float result = {};

	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

	return result;
}
// 正規化
Vector3 Vector3Mas::Normalize(const Vector3& v) {
	Vector3 result = {};

	float len = Length(v);

	if (len == 0.0f) {
		return {0.0f, 0.0f, 0.0f};
	}

	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;

	return result;
}


void Vector3Mas::VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void Vector3Mas::Initialize() {
	v1_ = {1.0f, 3.0f, -5.0f};
	v2_ = {4.0f, -1.0f, 2.0f};
	k_ = 4.0f;
}

void Vector3Mas::Update() {
	resultAdd_ = Add(v1_, v2_);
	resultSubtract_ = Subtract(v1_, v2_);
	resultMultiply_ = Multiply(k_, v1_);
	resultDot_ = Dot(v1_, v2_);
	resultLength_ = Length(v1_);
	resultNormalize_ = Normalize(v2_);
}

void Vector3Mas::Draw() {
	//VectorScreenPrintf(0, 0, resultAdd_, " : Add");
	//VectorScreenPrintf(0, kRowHeight, resultSubtract_, ": Subtract");
	//VectorScreenPrintf(0, kRowHeight * 2, resultMultiply_, ": Multiply");
	//Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot_);
	//Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength_);
	//VectorScreenPrintf(0, kRowHeight * 5, resultNormalize_, ": Normalize");
}
