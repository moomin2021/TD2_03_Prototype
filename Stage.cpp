#include "Stage.h"
#include "DxLib.h"
#include "Easing.h"

Stage::Stage() :
#pragma region 初期化リスト
	pos_{0.0f, 0.0f},// -> 座標
	radius_(0.0f),// -> 半径
	maxRadius_(0.0f),// -> 最高半径
	minRadius_(0.0f),// -> 最低半径
	addRadius_(0.0f),// -> 加算値
	isContr_(false),// 収縮しているかフラグ(している = true)
	contrValue_(0.0f),// -> 収縮値
	contrStartTime_(0),// -> 収縮開始時間
	contrTime_(0.0f),// -> 収縮時間[s]
	startContrRadius_(0.0f)// -> 収縮開始時の半径
#pragma endregion
{}

void Stage::Initialize()
{
	pos_ = { 500.0f, 500.0f };// -> 座標
	radius_ = 500.0f;// -> 半径
	maxRadius_ = 500.0f;// -> 最高半径
	minRadius_ = 50.0f;// -> 最低半径
	addRadius_ = 0.1f;// -> 加算値

	isContr_ = false;// 収縮しているかフラグ(している = true)
	contrValue_ = 0.0f;// -> 収縮値
	contrStartTime_ = 0;// -> 収縮開始時間
	contrTime_ = 1.0f;// -> 収縮時間[s]
	startContrRadius_ = 0.0f;// -> 収縮開始時の半径
}

void Stage::Update()
{
	// 半径加算
	radius_ += addRadius_;

	// 現在の半径が最高値以上になったら最高値より大きくならないようにする
	if (radius_ >= maxRadius_) radius_ = maxRadius_;

	// 収縮フラグが[ON]なら
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
