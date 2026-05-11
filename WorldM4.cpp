#include "WorldM4.h"

WorldM4::~WorldM4() {}

// アフィン変換行列
Matrix4x4 WorldM4::MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) { 
	Matrix4x4 result = {};

	scaleMatrix_ = make_.MakeScaleMatrix(scale);
	mRotate_.SetRotate(rotate);
	mRotate_.Update();
	rotateMatrix_ = mRotate_.GetRotateXYZMatrix();
	translateMatrix_ = make_.MakeTransLateMatrix(translate);

	result = m4_.Multiply(scaleMatrix_,m4_.Multiply(rotateMatrix_,translateMatrix_));

	return result;
}

void WorldM4::Initialize() {
	scale_ = {1.2f, 0.79f, -2.1f};
	rotate_ = {0.4f, 1.43f, -0.8f};
	translate_ = {2.7f, -4.15f, 1.57f};
}

void WorldM4::Update() { 
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_); 
}

void WorldM4::Draw() { m4_.MatrixScreenPrintf(0, 20, worldMatrix_, "worldMatrix"); }
