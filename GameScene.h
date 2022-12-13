#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Player.h"
#include "Boss.h"
#include "Stage.h"
#include "Enemy.h"
#include <vector>

class GameScene : public BaseScene {
	// --メンバ変数-- //
public:

private:
	// キーボード入力
	Key* key_;

	// プレイヤー
	Player* player_;

	// ボス
	Boss* boss_;

	// ステージ
	Stage* stage_;

	// エネミー
	std::vector<Enemy*> enemys_;
	int maxEnemy_;

	// --メンバ関数-- //
public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

private:
	void Collision();// -> 当たり判定処理

};