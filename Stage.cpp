#include "Stage.h"
#include "DxLib.h"
#include "Easing.h"

Stage::Stage() :
#pragma region ���������X�g
	pos_{0.0f, 0.0f},// -> ���W
	radius_(0.0f),// -> ���a
	maxRadius_(0.0f),// -> �ō����a
	minRadius_(0.0f),// -> �Œᔼ�a
	addRadius_(0.0f),// -> ���Z�l
	isContr_(false),// ���k���Ă��邩�t���O(���Ă��� = true)
	contrValue_(0.0f),// -> ���k�l
	contrStartTime_(0),// -> ���k�J�n����
	contrTime_(0.0f),// -> ���k����[s]
	startContrRadius_(0.0f)// -> ���k�J�n���̔��a
#pragma endregion
{}

void Stage::Initialize()
{
	pos_ = { 500.0f, 500.0f };// -> ���W
	radius_ = 500.0f;// -> ���a
	maxRadius_ = 500.0f;// -> �ō����a
	minRadius_ = 50.0f;// -> �Œᔼ�a
	addRadius_ = 0.1f;// -> ���Z�l

	isContr_ = false;// ���k���Ă��邩�t���O(���Ă��� = true)
	contrValue_ = 0.0f;// -> ���k�l
	contrStartTime_ = 0;// -> ���k�J�n����
	contrTime_ = 1.0f;// -> ���k����[s]
	startContrRadius_ = 0.0f;// -> ���k�J�n���̔��a
}

void Stage::Update()
{
	// ���a���Z
	radius_ += addRadius_;

	// ���݂̔��a���ō��l�ȏ�ɂȂ�����ō��l���傫���Ȃ�Ȃ��悤�ɂ���
	if (radius_ >= maxRadius_) radius_ = maxRadius_;

	// ���k�t���O��[ON]�Ȃ�
	if (isContr_) {
		float nowTime = (GetNowCount() - contrStartTime_) / 1000.0f;

		float rate = nowTime / contrTime_;
		if (rate >= 1.0f) isContr_ = false;

		float endContr = radius_ - contrValue_;
		if (endContr <= minRadius_) endContr = minRadius_;

		radius_ = Easing::Quint::easeOut(startContrRadius_, endContr, rate);
	}
}

void Stage::Draw()
{
	DrawBoxAA(pos_.x - radius_, pos_.y - radius_,
		pos_.x + radius_, pos_.y + radius_,
		0xFF3333, false, 1.0f);
}

void Stage::Contraction(float contrValue)
{
	isContr_ = true;
	contrStartTime_ = GetNowCount();
	startContrRadius_ = radius_;
	contrValue_ += contrValue;
}
