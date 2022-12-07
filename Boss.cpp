#include "Boss.h"
#include "DxLib.h"

Boss::Boss() :
	// ボス
	pos_{0.0f, 0.0f},// -> 座標
	radius_(0.0f),// ----> 半径
	speed_(0.0f),// -----> 速度

	knockVec_{0.0f, 0.0f},// -> ノックバック方向
	knockSpeed_(0.0f),// -----> ノックバック速度

	// プレイヤーの座標
	playerPos_(nullptr)
{

}

Boss::~Boss()
{

}

void Boss::Initialize()
{
	// ボス
	pos_ = { 300.0f, 500.0f };// -> 座標
	radius_ = 64.0f;// -----------> 半径
}

void Boss::Update()
{
	// 状態別更新処理
	(this->*actionTable[state_])();


}

void Boss::Draw()
{
	DrawCircleAA(pos_.x, pos_.y, radius_, 100, 0xFF0000, true);
	DrawFormatString(0, 0, 0xFFFFFF, "playerPos = {%f, %f}", playerPos_->x, playerPos_->y);
}

void (Boss::* Boss::actionTable[]) () = {
	&Boss::Normal,// -> 通常状態
	&Boss::Knock// ---> ノックバック状態
};

void Boss::Normal()
{

}

void Boss::Knock()
{
	// ノックバック方向に移動
	pos_ += knockVec_ * knockSpeed_;

	// ノックバック速度を減算
	knockSpeed_ -= 0.1f;

	// ノックバック速度が0以下になったら通常状態にする
	if (knockSpeed_ <= 0) state_ = BossState::NORMAL;
}
