#include "SphereSecond.h"
#include <Novice.h>
#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG



bool SphereSecond::IsCollsion(const Sphere& s1, const Sphere& s2) { 
	
	float dx = s1.center.x - s2.center.x;
	float dy = s1.center.y - s2.center.y;
	float dz = s1.center.z - s2.center.z;

	float distanceSq = (dx * dx) + (dy * dy) + (dz * dz);

	float radiusSum = s1.radius + s2.radius;

	float radiusSumSq = radiusSum * radiusSum;	

	return distanceSq <= radiusSumSq;

}

void SphereSecond::DrawGrid(const Matrix4x4& viewProjectonMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;                                      // Gridの半分の幅
	const uint32_t kSubdivision = 10;                                       // Gridの分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision); // 1つ分の長さ
	const uint32_t kCenterIndex = kSubdivision / 2;
	// 奥から手前の線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		// 上に書かれているコードを使ってワールド座標系上の始点と終点を求める
		float x = -kGridHalfWidth + (float(xIndex) * kGridEvery);
		Vector3 startPos = {x, 0.0f, -kGridHalfWidth};
		Vector3 endPos = {x, 0.0f, kGridHalfWidth};
		// スクリーン座標系まで変換を掛ける
		Vector3 dcStart = MM_.Transform(startPos, viewProjectonMatrix);
		Vector3 screenStart = MM_.Transform(dcStart, viewportMatrix);

		Vector3 dcEnd = MM_.Transform(endPos, viewProjectonMatrix);
		Vector3 screenEnd = MM_.Transform(dcEnd, viewportMatrix);

		// 変換した座標を使って表示する。色はうすい灰色(0xAAAAAAFF)、原点は黒ぐらいがおすすめだが、色は何でもいい
		uint32_t color = (xIndex == kCenterIndex) ? BLACK : 0xAAAAAAFF;
		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, color);
	}
	// 左から右も同じように順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		// 奥から手前が左右に代わるだけである
		float z = -kGridHalfWidth + (float(zIndex) * kGridEvery);
		Vector3 startPos = {-kGridHalfWidth, 0.0f, z};
		Vector3 endPos = {kGridHalfWidth, 0.0f, z};
		// スクリーン座標系まで変換を掛ける
		Vector3 dcStart = MM_.Transform(startPos, viewProjectonMatrix);
		Vector3 screenStart = MM_.Transform(dcStart, viewportMatrix);

		Vector3 dcEnd = MM_.Transform(endPos, viewProjectonMatrix);
		Vector3 screenEnd = MM_.Transform(dcEnd, viewportMatrix);

		// 変換した座標を使って表示する。色はうすい灰色(0xAAAAAAFF)、原点は黒ぐらいがおすすめだが、色は何でもいい
		uint32_t color = (zIndex == kCenterIndex) ? BLACK : 0xAAAAAAFF;
		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, color);
	}
}
// 球体
void SphereSecond::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 10; // 球体の分割数
	phi_ = std::acos(-1.0f);
	const float kLonEvery = (2.0f * phi_) / kSubdivision; // 経度分割1つ分の角度
	const float kLatEvery = phi_ / kSubdivision;          // 緯度分割1つ分の角度
	// 緯度の方向に分割していく　-π/2~π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -phi_ / 2.0f + kLatEvery * latIndex; // 現在の緯度
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度
			// World座標系でのa,b,cを求める
			Vector3 a, b, c;
			// a,b,cをScreen座標系まで変換
			a = {sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon), sphere.center.y + sphere.radius * std::sin(lat), sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon)};
			b = {
			    sphere.center.x + sphere.radius * std::cos(lat + kLatEvery) * std::cos(lon), sphere.center.y + sphere.radius * std::sin(lat + kLatEvery),
			    sphere.center.z + sphere.radius * std::cos(lat + kLatEvery) * std::sin(lon)};
			c = {
			    sphere.center.x + sphere.radius * std::cos(lat) * std::cos(lon + kLonEvery), sphere.center.y + sphere.radius * std::sin(lat),
			    sphere.center.z + sphere.radius * std::cos(lat) * std::sin(lon + kLonEvery)};

			Vector3 dcA, dcB, dcC;
			Vector3 ScreenA, ScreenB, ScreenC;
			dcA = MM_.Transform(a, viewProjectMatrix);
			ScreenA = MM_.Transform(dcA, viewportMatrix);

			dcB = MM_.Transform(b, viewProjectMatrix);
			ScreenB = MM_.Transform(dcB, viewportMatrix);

			dcC = MM_.Transform(c, viewProjectMatrix);
			ScreenC = MM_.Transform(dcC, viewportMatrix);

			// ab,bcで線を引く
			Novice::DrawLine((int)ScreenA.x, (int)ScreenA.y, (int)ScreenB.x, (int)ScreenB.y, color);
			Novice::DrawLine((int)ScreenA.x, (int)ScreenA.y, (int)ScreenC.x, (int)ScreenC.y, color);
		}
	}
}
	

void SphereSecond::Initialize() { 
	Sphere_.Initialize();

	sphere0_.center = {1.0f,0.0f,0.0f};
	sphere0_.radius = 0.3f;
	sphere1_.center = {};
	sphere1_.radius = 1.0f;

	
	
}

void SphereSecond::Update(char* keys) {
	
#ifdef _DEBUG
	ImGui::Begin("Window");
	ImGui::DragFloat3("sphere[0].center", &sphere0_.center.x, 0.01f);
	ImGui::DragFloat("sphere[0].radius", &sphere0_.radius, 0.01f);
	ImGui::DragFloat3("sphere[1].center", &sphere1_.center.x, 0.01f);
	ImGui::DragFloat("sphere[1].radius", &sphere1_.radius, 0.01f);

	ImGui::End();

	float cameraSpeed = 0.05f;
	if (keys[DIK_E]) {
		cameraTranslate_.z += cameraSpeed;
	}
	if (keys[DIK_Q]) {
		cameraTranslate_.z -= cameraSpeed;
	}
	if (keys[DIK_A]) {
		cameraTranslate_.x += cameraSpeed;
	}
	if (keys[DIK_D]) {
		cameraTranslate_.x -= cameraSpeed;
	}
	if (keys[DIK_W]) {
		cameraTranslate_.y -= cameraSpeed;
	}
	if (keys[DIK_S]) {
		cameraTranslate_.y += cameraSpeed;
	}
	if (keys[DIK_UP]) {
		cameraRotate_.x += cameraSpeed/5;
	}
	if (keys[DIK_DOWN]) {
		cameraRotate_.x -= cameraSpeed/5;
	}
	if (keys[DIK_LEFT]) {
		cameraRotate_.y += cameraSpeed/5;
	}
	if (keys[DIK_RIGHT]) {
		cameraRotate_.y -= cameraSpeed/5;
	}
	

#endif // _DEBUG
 isCollision_=IsCollsion(sphere0_, sphere1_);

// 各種行列の計算
 RPV2_.WorldViewPortMatrix(cameraMatrix_, worldMatrix_, viewMatrix_, projectionMatrix_);
 cameraMatrix_ = wm4_.MakeAffineMatrix({1.0f, 1.0f, 1.0f}, cameraRotate_, cameraTranslate_);
 worldMatrix_ = wm4_.MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
 viewMatrix_ = m4_.Inverse(cameraMatrix_);
 projectionMatrix_ = RPV2_.MakePerspectiveFovMatrix(0.45f, float(KWindowWidth) / float(KWindowHeight), 0.1f, 100.0f);
 //  ViewProjectionMatrixを作る
 viewProjectionMatrix_ = m4_.Multiply(viewMatrix_, projectionMatrix_);
 viewPortMatrix_ = RPV2_.MakeViewportMatrix(0, 0, float(KWindowWidth), float(KWindowHeight), 0.0f, 1.0f);
}

void SphereSecond::Draw() { 
	SphereSecond::DrawGrid(viewProjectionMatrix_, viewPortMatrix_);
	uint32_t color = isCollision_ ? RED : WHITE;
	SphereSecond::DrawSphere(sphere0_, viewProjectionMatrix_, viewPortMatrix_, color);
	SphereSecond::DrawSphere(sphere1_, viewProjectionMatrix_, viewPortMatrix_, WHITE);
}
