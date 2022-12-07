#include "GameScene.h"

bool CircleCol(Vector2 pos1, float r1, Vector2 pos2, float r2) {
	float a = pos1.x - pos2.x;
	float b = pos1.y - pos2.y;
	float c = sqrtf(a * a + b * b);

	if (c <= r1 + r2) return true;
	return false;
}

GameScene::GameScene() :
	key_(nullptr),// -> キーボード入力
	player_(nullptr),// -> プレイヤー
	boss_(nullptr)// -> ボス
{

}

GameScene::~GameScene()
{
	delete player_;
	delete boss_;
}

void GameScene::Initialize()
{
	// キーボード入力
	key_ = Key::GetInstance();

	// プレイヤー
	player_ = new Player();
	player_->Initialize();

	// ボス
	boss_ = new Boss();
	boss_->Initialize();

	// プレイヤーとボスお互いの座標を設定する
	player_->SetBossPos(&boss_->GetPos());
	boss_->SetPlayerPos(&player_->GetPos());
}

void GameScene::Update()
{
	// プレイヤー
	player_->Update();

	// ボス
	boss_->Update();

	// 当たり判定処理
	Collision();
}

void GameScene::Draw()
{
	// プレイヤー
	player_->Draw();

	// ボス
	boss_->Draw();
}

void GameScene::Collision()
{
	for (auto it = player_->GetBuulets().begin(); it != player_->GetBuulets().end();) {
		// ボスに当たったら弾を削除
		if (CircleCol(it->GetPos(), 8.0f, boss_->GetPos(), 64.0f)) {
			// ボスの状態が通常状態なら
			if (boss_->GetState() == Boss::BossState::NORMAL) {
				boss_->SetState(Boss::BossState::KNOCK);// -> ノック状態に変更
				boss_->SetKnockSpeed(2.0f);// -> ノックバックの速度を設定

				// 弾からボスまでのベクトルを計算
				Vector2 b2bVec = boss_->GetPos() - it->GetPos();
				b2bVec.normalize();// -> 正規化
				boss_->SetKnockVec(b2bVec);// -> ノックバックの方向を設定
			}

			// 当たった弾を削除
			it = player_->GetBuulets().erase(it);
		}
		else ++it;
	}
}
