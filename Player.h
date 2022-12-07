#pragma once
#include "Key.h"
#include "Vector2.h"
#include "Bullet.h"
#include <vector>

class Player {
	// 状態
	enum PlayerState {
		NORMAL// -> 通常
	};

	// --メンバ変数-- //
public:

private:
	// キーボード入力クラス
	Key* key_;

	// 弾
	std::vector<Bullet> bullets_;

	// プレイヤー
	Vector2 pos_;// -> 座標
	float radius_;// -> 半径
	float speed_;// -> 速度

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

	// 弾を取得
	std::vector<Bullet> &GetBuulets() { return bullets_; }
#pragma endregion

private:
	// 状態別更新処理
	static void (Player::* actionTable[]) ();

	// 通常状態
	void Normal();

	void Move();// -> 移動処理
	void BulletShot();// -> 弾の発射処理
	void DeleteBullet();// -> 弾の削除処理
};