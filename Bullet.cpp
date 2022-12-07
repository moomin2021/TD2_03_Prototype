#include "Bullet.h"
#include "DxLib.h"

Bullet::Bullet() :
	pos_{0.0f, 0.0f},// ----> ���W
	radius_(0.0f),// -------> ���a
	speed_(0.0f),// --------> ���x
	moveVec_{0.0f, 0.0f}// -> �ړ�����
{

}

Bullet::~Bullet()
{

}

void Bullet::Initialize()
{
	radius_ = 8.0f;// -> ���a
	speed_ = 4.0f;// -> ���x
}

void Bullet::Update()
{
	// �ړ�����
	pos_ += moveVec_ * speed_;
}

void Bullet::Draw()
{
	DrawCircleAA(pos_.x, pos_.y, radius_, 20, 0xFFFFFF, true);
}
