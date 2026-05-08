#pragma once
//#include "Matrix4.h"
//#include "Vector3Mas.h"
#include "Object.h"
#include"MakeMatrix.h"
#include <Novice.h>
#include <cmath>

class Rotate{
public:
	
	~Rotate();

	// 1.X軸回転行列
	Matrix4x4 MakeRotateXMatrix(float radian);

	// 2.Y軸回転行列
	Matrix4x4 MakeRotateYMatrix(float radian);

	// 3.Z軸回転行列
	Matrix4x4 MakeRotateZMatrix(float radian);

	void Initialize();

	void Update();

	void Draw();

private:
	Matrix4 m4_;

	Vector3 rotate_;

	Matrix4x4 rotateMatrixX_;
	Matrix4x4 rotateMatrixY_;
	Matrix4x4 rotateMatrixZ_;
	Matrix4x4 rotateXYZMatrix_;
};

