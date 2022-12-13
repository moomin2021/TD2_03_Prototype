#pragma once
#include "Key.h"
#include "Vector2.h"
#include "Bullet.h"
#include <vector>

class Player {
public:
	// 状態
	enum PlayerState {
		NORMAL,// -> ノーマル
		CHARGE,// -> チャージ
		DASH// -> ダッシュ
	};

	// --メンバ変数-- //
public:

private:
	// キーボード入力クラス
	Key* key_;

	// プレイヤー
	Vector2 pos_;// -> 座標
	float radius_;// -> 半径
	int nowState_;// -> 現在の状態

	float stdSpeed_;// ----> 標準速度
	float nowSpeed_;// ----> 現在の速度
	float addSpeed_;// ----> 速度の加算値
	float subSpeed_;// ----> 速度の減算値
	float minSpeed_;// ----> 速度の最小値
	float maxSpeed_;// ----> 速度の最高値
	float chargeSpeed_;// -> チャージした速度

	// チャージ
	float maxChargeTime_;// -> 最高チャージ時間[s]
	int chargeStartTime_;// -> チャージ開始時間

	Vector2 dashVec_;// -> ダッシュ方向

	// ボスの座標
	Vector2* bossPos_;

	// --メンバ関数-- //
public:
	// コンストラクタ
	Player();

	// デストラクタ
	~Player();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

#pragma region セッター
	// ボスの座標を設定
	void SetBossPos(Vector2* bossPos) { bossPos_ = bossPos; }
#pragma endregion

#pragma region ゲッター
	// 座標を取得する
	Vector2& GetPos() { return pos_; }

	// ダッシュベクトル取得
	Vector2& GetDashVec() { return dashVec_; }

	// 半径を取得
	float GetRadius() { return radius_; }

	// 状態を取得
	int GetState() { return nowState_; }

	// 現在の速度を取得
	float GetSpeed() { return nowSpeed_; }
#pragma endregion

private:
	// 状態別更新処理
	static void (Player::* actionTable[]) ();

	// 状態別処理
	void Normal();// -> ノーマル状態時処理
	void Charge();// -> チャージ状態時処理
	void Dash();// ---> ダッシュ状態時処理

	void Move();// -> 移動処理
	void DashVec();// -> ダッシュベクトル
	void ChargeTrigger();// -> チャージ状態への変更処理
};