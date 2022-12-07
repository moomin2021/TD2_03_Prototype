#include "Player.h"
#include "DxLib.h"

Player::Player() :
	key_(nullptr),// -> キーボード入力

	bullets_{},// -> 弾

	// プレイヤー
	pos_{ 0.0f, 0.0f },// -> 座標
	radius_(0.0f),// ------> 半径
	speed_(0.0f),// -------> 速度

	// ボスの座標
	bossPos_(nullptr)
{}

Player::~Player()
{

}

void Player::Initialize()
{
	// キーボード入力クラス
	key_ = Key::GetInstance();

	// プレイヤー
	pos_ = { 700.0f, 500.0f };// -> 座標
	radius_ = 16.0f;// -----------> 半径
	speed_ = 2.0f;// -------------> 速度
}

void Player::Update()
{
	// プレイヤー状態別更新処理
	(this->*actionTable[PlayerState::NORMAL])();

	// 弾の更新処理
	for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
		it->Update();
	}
}

void Player::Draw()
{
	// プレイヤーの描画
	DrawCircleAA(pos_.x, pos_.y, radius_, 20, 0xFFFFFF, true);

	// 弾の描画処理
	for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
		it->Draw();
	}

	// デバック表示
	DrawFormatString(0, 20, 0xFFFFFF, "size = %d", bullets_.size());
}

void (Player::* Player::actionTable[]) () = {
	&Player::Normal,// -> 通常状態
};

void Player::Normal()
{
	Move();// -> 移動処理
	BulletShot();// -> 弾の発射処理
	DeleteBullet();// -> 弾の削除処理
}

void Player::Move()
{
	pos_.x += (key_->PushKey(KEY_INPUT_D) - key_->PushKey(KEY_INPUT_A)) * speed_;
	pos_.y += (key_->PushKey(KEY_INPUT_S) - key_->PushKey(KEY_INPUT_W)) * speed_;
}

void Player::BulletShot()
{
	// 弾発射処理
	if (key_->ReleaseKey(KEY_INPUT_SPACE)) {
		// 弾を生成
		Bullet* bullet = new Bullet();
		bullet->Initialize();// -> 初期化処理
		bullet->SetPos(pos_);// -> 座標設定

		// 弾の移動方向を設定
		Vector2 p2bVec = *bossPos_ - pos_;// -> プレイヤーからボスまでのベクトル
		p2bVec.normalize();// -> 正規化
		bullet->SetMoveVec(p2bVec);// -> 移動方向を設定

		bullets_.push_back(*bullet);
	}
}

void Player::DeleteBullet()
{
	for (auto it = bullets_.begin();it != bullets_.end();) {
		// 画面外に行ったら削除
		if (it->GetPos().x < -8.0f) it = bullets_.erase(it);
		else if (it->GetPos().x > 1008.0f) it = bullets_.erase(it);
		else if (it->GetPos().y < -8.0f) it = bullets_.erase(it);
		else if (it->GetPos().y > 1008.0f) it = bullets_.erase(it);
		else ++it;
	}
}
