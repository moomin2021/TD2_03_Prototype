#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet() :
	pos_{0.0f, 0.0f},// ----> À•W
	radius_(0.0f),// -------> ”¼Œa
	speed_(0.0f),// --------> ‘¬“x
	moveVec_{0.0f, 0.0f}// -> ˆÚ“®•ûŒü
{

}

Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	radius_ = 8.0f;// -> ”¼Œa
	speed_ = 4.0f;// -> ‘¬“x
}

void Bullet::Update()
{
	// ˆÚ“®ˆ—
	pos_ += moveVec_ * speed_;
}

void Bullet::Draw()
{
	DrawCircleAA(pos_.x, pos_.y, radius_, 20, 0xFFFFFF, true);
}
