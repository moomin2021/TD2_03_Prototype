#include "Stage.h"
#include "DxLib.h"
#include "Easing.h"

Stage::Stage() :
#pragma region ‰Šú‰»ƒŠƒXƒg
	pos_{0.0f, 0.0f},// -> À•W
	radius_(0.0f),// -> ”¼Œa
	maxRadius_(0.0f),// -> Å‚”¼Œa
	minRadius_(0.0f),// -> Å’á”¼Œa
	addRadius_(0.0f),// -> ‰ÁŽZ’l
	isContr_(false),// Žûk‚µ‚Ä‚¢‚é‚©ƒtƒ‰ƒO(‚µ‚Ä‚¢‚é = true)
	contrValue_(0.0f),// -> Žûk’l
	contrStartTime_(0),// -> ŽûkŠJŽnŽžŠÔ
	contrTime_(0.0f),// -> ŽûkŽžŠÔ[s]
	startContrRadius_(0.0f)// -> ŽûkŠJŽnŽž‚Ì”¼Œa
#pragma endregion
{}

void Stage::Initialize()
{
	pos_ = { 500.0f, 500.0f };// -> À•W
	radius_ = 500.0f;// -> ”¼Œa
	maxRadius_ = 500.0f;// -> Å‚”¼Œa
	minRadius_ = 50.0f;// -> Å’á”¼Œa
	addRadius_ = 0.1f;// -> ‰ÁŽZ’l

	isContr_ = false;// Žûk‚µ‚Ä‚¢‚é‚©ƒtƒ‰ƒO(‚µ‚Ä‚¢‚é = true)
	contrValue_ = 0.0f;// -> Žûk’l
	contrStartTime_ = 0;// -> ŽûkŠJŽnŽžŠÔ
	contrTime_ = 1.0f;// -> ŽûkŽžŠÔ[s]
	startContrRadius_ = 0.0f;// -> ŽûkŠJŽnŽž‚Ì”¼Œa
}

void Stage::Update()
{
	// ”¼Œa‰ÁŽZ
	radius_ += addRadius_;

	// Œ»Ý‚Ì”¼Œa‚ªÅ‚’lˆÈã‚É‚È‚Á‚½‚çÅ‚’l‚æ‚è‘å‚«‚­‚È‚ç‚È‚¢‚æ‚¤‚É‚·‚é
	if (radius_ >= maxRadius_) radius_ = maxRadius_;

	// Žûkƒtƒ‰ƒO‚ª[ON]‚È‚ç
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
