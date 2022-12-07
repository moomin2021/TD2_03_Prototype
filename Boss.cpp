#include "Boss.h"
#include "DxLib.h"

Boss::Boss() :
	// �{�X
	pos_{0.0f, 0.0f},// -> ���W
	radius_(0.0f),// ----> ���a
	speed_(0.0f),// -----> ���x

	knockVec_{0.0f, 0.0f},// -> �m�b�N�o�b�N����
	knockSpeed_(0.0f),// -----> �m�b�N�o�b�N���x

	// �v���C���[�̍��W
	playerPos_(nullptr)
{

}

Boss::~Boss()
{

}

void Boss::Initialize()
{
	// �{�X
	pos_ = { 300.0f, 500.0f };// -> ���W
	radius_ = 64.0f;// -----------> ���a
}

void Boss::Update()
{
	// ��ԕʍX�V����
	(this->*actionTable[state_])();


}

void Boss::Draw()
{
	DrawCircleAA(pos_.x, pos_.y, radius_, 100, 0xFF0000, true);
	DrawFormatString(0, 0, 0xFFFFFF, "playerPos = {%f, %f}", playerPos_->x, playerPos_->y);
}

void (Boss::* Boss::actionTable[]) () = {
	&Boss::Normal,// -> �ʏ���
	&Boss::Knock// ---> �m�b�N�o�b�N���
};

void Boss::Normal()
{

}

void Boss::Knock()
{
	// �m�b�N�o�b�N�����Ɉړ�
	pos_ += knockVec_ * knockSpeed_;

	// �m�b�N�o�b�N���x�����Z
	knockSpeed_ -= 0.1f;

	// �m�b�N�o�b�N���x��0�ȉ��ɂȂ�����ʏ��Ԃɂ���
	if (knockSpeed_ <= 0) state_ = BossState::NORMAL;
}
