#pragma once
#include "Object.h"
#include "Matrix4.h"
#include <cmath>

class RringPlineVer2 {
public:
	
	~RringPlineVer2();

	// 1.透視投影行列
	Matrix4x4 MakePerspectiveFovMatrix(
		float fovY, float aspectRatio, 
		float nearClip, float farClip);
	// 2.正射影行列
	Matrix4x4 MakeOrthographicMatrix(
		float left,float top,
		float right,float bottom,
		float nearClip,float farClip);
	// 3.ビューポート行列
	Matrix4x4 MakeViewportMatrix(
		float left, float top, 
		float width, float height,
		float minDepth, float maxDepth);

	void Initialize();

	void Update();

	void Draw();

private:
	Matrix4x4 orthographicMatrix_;
	Matrix4x4 perspectiveFovMatrix_;
	Matrix4x4 viewportMatrix_;

	Matrix4 m4_;
};

