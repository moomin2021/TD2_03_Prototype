#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet() :
	pos_{0.0f, 0.0f},// ----> 座標
	radius_(0.0f),// -------> 半径
	speed_(0.0f),// --------> 速度
	moveVec_{0.0f, 0.0f}// -> 移動方向
{

}

Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	radius_ = 8.0f;// -> 半径
	speed_ = 4.0f;// -> 速度
}

void Bullet::Update()
{
	// 移動処理
	pos_ += moveVec_ * speed_;
}

void Bullet::Draw()
{
	DrawCircleAA(pos_.x, pos_.y, radius_, 20, 0xFFFFFF, true);
}
