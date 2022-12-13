#pragma once
#include "Vector2.h"

class Enemy {
	// 状態
	enum EnemyState {
		NORMAL,// -> ノーマル状態
		KNOCK// -> ノックバック状態
	};

	// --メンバ変数-- //
public:

private:
	Vector2 pos_;// -> 座標
	float radius_;// -> 半径
	int nowState_;// -> 状態

	// --メンバ関数-- //
public:
	// コンストラクタ
	Enemy();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

#pragma region セッター
	// 座標を設定
	void SetPos(Vector2 pos) { pos_ = pos; }
#pragma endregion

#pragma region ゲッター
	// 座標を取得
	Vector2 GetPos() { return pos_; }

	// 半径の取得
	float GetRadius() { return radius_; }
#pragma endregion

private:
	// 状態別更新処理
	static void (Enemy::* actionTable[]) ();

	void Normal();// -> 通常状態
	void Knock();// -> ノックバック状態
};