#pragma once
#include "Vector2.h"

class Bullet {
	// --メンバ変数-- //
public:

private:
	Vector2 pos_;// -> 座標
	float radius_;// -> 半径
	float speed_;// -> 速度
	Vector2 moveVec_;// -> 移動方向

	// --メンバ関数-- //
public:
	// コンストラクタ
	Bullet();

	// デストラクタ
	~Bullet();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

#pragma region セッター
	// 座標を設定
	void SetPos(Vector2 pos) { pos_ = pos; }

	// 移動方向を設定
	void SetMoveVec(Vector2 moveVec) { moveVec_ = moveVec; }
#pragma endregion

#pragma region ゲッター
	// 座標を取得
	Vector2 GetPos() { return pos_; }
#pragma endregion

private:

};