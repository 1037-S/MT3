#pragma once


struct Vector3 {
	float x;
	float y;
	float z;
};

static const int kColumnWidth = 60;
static const int kRowHeight = 20;


class Vector3Mas {
public:
	
	~Vector3Mas();

	// 加算
	Vector3 Add(const Vector3& v1, const Vector3& v2);
	// 減算
	Vector3 Subtract(const Vector3& v1, const Vector3& v2); 
	// スカラー倍
	Vector3 Multiply(float scalar, const Vector3& v);
	// 内積
	float Dot(const Vector3& v1, const Vector3& v2); 
	// 長さ(ノルム)
	float Length(const Vector3& v);
	// 正規化
	Vector3 Normalize(const Vector3& v);

	void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label);

	void Initialize();

	void Update();

	void Draw();

private:
	Vector3 v1_;
	Vector3 v2_;
	float k_;

	Vector3 resultAdd_;
	Vector3 resultSubtract_;
	Vector3 resultMultiply_;
	float resultDot_;
	float resultLength_;
	Vector3 resultNormalize_;
};