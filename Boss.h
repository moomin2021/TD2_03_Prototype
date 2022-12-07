#pragma once
#include "Vector2.h"

class Boss {
public:
	// 状態
	enum BossState {
		NORMAL,// -> 通常状態
		KNOCK,// --> ノックバック状態
	};

	// --メンバ変数-- //
public:

private:
	// ボス
	int state_;// ----> 状態
	Vector2 pos_;// --> 座標
	float radius_;// -> 半径
	float speed_;// --> 速度

	// ノックバック
	Vector2 knockVec_;// -> ノックバック方向
	float knockSpeed_;// -> ノックバック速度

	// プレイヤーの座標
	Vector2* playerPos_;

	// --メンバ関数-- //
public:
	// コンストラクタ
	Boss();

	// デストラクタ
	~Boss();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

#pragma region セッター
	// プレイヤーの座標を設定
	void SetPlayerPos(Vector2* playerPos) { playerPos_ = playerPos; }

	// 状態設定
	void SetState(int state) { state_ = state; }

	// ノックバック方向設定
	void SetKnockVec(Vector2 knockVec) { knockVec_ = knockVec; }

	// ノックバック速度設定
	void SetKnockSpeed(float knockSpeed) { knockSpeed_ = knockSpeed; }
#pragma endregion

#pragma region ゲッター
	// ボスの座標を取得
	Vector2 &GetPos() { return pos_; }

	// 状態を取得
	int GetState() { return state_; }
#pragma endregion

private:
	// 状態別更新処理
	static void (Boss::* actionTable[]) ();

	void Normal();// -> 通常状態
	void Knock();// -> ノックバック状態

};