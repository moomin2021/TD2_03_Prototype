#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy() :
#pragma region ���������X�g
	pos_{0.0f, 0.0f},// -> ���W
	radius_(0.0f)// -> ���a
#pragma endregion
{
}

void Enemy::Initialize()
{
	radius_ = 16.0f;// -> ���a
}

void Enemy::Update()
{

}

void Enemy::Draw()
{
	DrawCircleAA(pos_.x, pos_.y, radius_, 20, 0xFF0000, true);
}

void Enemy::Normal()
{
}

void Enemy::Knock()
{
}
