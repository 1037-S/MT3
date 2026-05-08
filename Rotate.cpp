#include "Rotate.h"

Rotate::~Rotate() {}
// 1.X軸回転行列
Matrix4x4 Rotate::MakeRotateXMatrix(float radian) {
	Matrix4x4 result{};

	result.m[0][0] = 1.0f;
	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = -std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[3][3] = 1.0f;

	return result;
}
// 2.Y軸回転行列
Matrix4x4 Rotate::MakeRotateYMatrix(float radian) {
	Matrix4x4 result{};

	result.m[0][0] = std::cos(radian);
	result.m[0][2] = -std::sin(radian);
	result.m[1][1] = 1.0f;
	result.m[2][0] = std::sin(radian);
	result.m[2][2] = std::cos(radian);
	result.m[3][3] = 1.0f;

	return result;
}
// 3.Z軸回転行列
Matrix4x4 Rotate::MakeRotateZMatrix(float radian) {
	Matrix4x4 result{};

	result.m[0][0] = std::cos(radian);
	result.m[0][1] = std::sin(radian);
	result.m[1][0] = -std::sin(radian);
	result.m[1][1] = std::cos(radian);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	return result;
}

void Rotate::Initialize() { rotate_ = {0.4f, 1.43f, -0.8f}; }

void Rotate::Update() {
	rotateMatrixX_ = MakeRotateXMatrix(rotate_.x);
	rotateMatrixY_ = MakeRotateYMatrix(rotate_.y);
	rotateMatrixZ_ = MakeRotateZMatrix(rotate_.z);

	rotateXYZMatrix_ = m4_.Multiply(rotateMatrixX_, m4_.Multiply(rotateMatrixY_, rotateMatrixZ_));
}

void Rotate::Draw() {
	Novice::ScreenPrintf(0, 0, "rotateMatrixX");
	m4_.MatrixScreenPrintf(0, 20, rotateMatrixX_, "rotateMatrixX");
	Novice::ScreenPrintf(0, kRowHeight * 5, "rotateMatrixY");
	m4_.MatrixScreenPrintf(0, 20 + kRowHeight * 5, rotateMatrixY_, "rotateMatrixY");
	Novice::ScreenPrintf(0, kRowHeight * 5 * 2, "rotateMatrixZ");
	m4_.MatrixScreenPrintf(0, 20 + kRowHeight * 5 * 2, rotateMatrixZ_, "rotateMatrixZ");
	Novice::ScreenPrintf(0, kRowHeight * 5 * 3, "rotateXYZMatrix");
	m4_.MatrixScreenPrintf(0, 20 + kRowHeight * 5 * 3, rotateXYZMatrix_, "rotateXYZMatrix");
}
