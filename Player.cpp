#include "Player.h"
#include "DxLib.h"
#include "Easing.h"

Player::Player() :
#pragma region 初期化リスト
	key_(nullptr),// -> キーボード入力

	// プレイヤー
	pos_{ 0.0f, 0.0f },// -> 座標
	radius_(0.0f),// ------> 半径
	nowState_(0),// -> 現在の状態

	stdSpeed_(0.0f),// ----> 標準速度
	nowSpeed_(0.0f),// ----> 現在の速度
	addSpeed_(0.0f),// ----> 速度の加算値
	subSpeed_(0.0f),// ----> 速度の減算値
	minSpeed_(0.0f),// ----> 速度の最小値
	maxSpeed_(0.0f),// ----> 速度の最高値
	chargeSpeed_(0.0f),// -> チャージした速度

	maxChargeTime_(0.0f),// -> 最高チャージ時間
	chargeStartTime_(0),// -> チャージ開始時間

	dashVec_{ 0.0f, 0.0f },// -> ダッシュ方向

	// ボスの座標
	bossPos_(nullptr)
#pragma endregion
{}

Player::~Player()
{

}

void Player::Initialize()
{
	// キーボード入力クラス
	key_ = Key::GetInstance();

	// プレイヤー
	pos_ = { 700.0f, 500.0f };// -------> 座標
	radius_ = 16.0f;// -----------------> 半径
	nowState_ = PlayerState::NORMAL;// -> ノーマル状態

	stdSpeed_ = 2.0f;// ---------> 標準速度
	nowSpeed_ = stdSpeed_;// ----> 現在の速度
	addSpeed_ = 0.1f;// --------> 速度の加算値
	subSpeed_ = 0.01f;// --------> 速度の減算値
	minSpeed_ = 0.1f;// ---------> 速度の最小値
	maxSpeed_ = 10.0f;// --------> 速度の最高値
	chargeSpeed_ = stdSpeed_;// -> チャージした速度

	maxChargeTime_ = 3.0f;// -> 最高チャージ時間[s]
	chargeStartTime_ = 0;// -> チャージ開始時間

	dashVec_ = { -1.0f, 0.0f };// -> 左方向に設定
}

void Player::Update()
{
	// プレイヤー状態別更新処理
	(this->*actionTable[nowState_])();
}

void Player::Draw()
{
	// プレイヤーの描画
	DrawCircleAA(pos_.x, pos_.y, radius_, 20, 0xFFFFFF, true);

	DrawFormatString(0, 20, 0xFFFFFF, "nowSpeed = %f", nowSpeed_);
	DrawFormatString(0, 40, 0xFFFFFF, "dashVec = { %f, %f }", dashVec_.x, dashVec_.y);
}

void (Player::* Player::actionTable[]) () = {
	&Player::Normal,// -> ノーマル状態
	&Player::Charge,// -> チャージ状態
	&Player::Dash,// ---> ダッシュ状態
};

void Player::Normal()
{
	Move();// -> 移動処理
	ChargeTrigger();// -> チャージ状態への変更処理
	DashVec();
}

void Player::Charge()
{
	Move();// -> 移動処理
	DashVec();

	// チャージ開始時間からの経過時間
	float nowTime = (GetNowCount() - chargeStartTime_) / 1000.0f;

	// チャージ率
	float chargeRate = nowTime / maxChargeTime_;
	if (chargeRate > 1.0f) chargeRate = 1.0f;// -> チャージ率が1.0より大きかったら1.0に固定

	// チャージ率で速度変更
	nowSpeed_ = Easing::Quint::easeOut(stdSpeed_, minSpeed_, chargeRate);

	// チャージ率でチャージ速度を変更
	chargeSpeed_ = Easing::Quint::easeOut(stdSpeed_ + 3.0f, maxSpeed_, chargeRate);

	// [SPACE]を離したら
	if (key_->ReleaseKey(KEY_INPUT_SPACE)) {
		nowState_ = PlayerState::DASH;// -> ダッシュ状態に変更
		nowSpeed_ = chargeSpeed_;// -> 現在の速度にチャージ速度を代入
	}
}

void Player::Dash()
{
	// 速度減衰
	nowSpeed_ -= 0.1f;

	// 現在の速度が標準速度まで下がったら
	if (nowSpeed_ <= stdSpeed_) {
		nowSpeed_ = stdSpeed_;// -> 標準速度に設定
		nowState_ = PlayerState::NORMAL;// -> ノーマル状態に設定
	}

	// ダッシュ方向に移動
	pos_ += dashVec_ * nowSpeed_;
}

void Player::Move()
{
	pos_.x += (key_->PushKey(KEY_INPUT_D) - key_->PushKey(KEY_INPUT_A)) * nowSpeed_;
	pos_.y += (key_->PushKey(KEY_INPUT_S) - key_->PushKey(KEY_INPUT_W)) * nowSpeed_;
}

void Player::DashVec()
{
	Vector2 inputVec;
	inputVec.x = key_->PushKey(KEY_INPUT_D) - key_->PushKey(KEY_INPUT_A);
	inputVec.y = key_->PushKey(KEY_INPUT_S) - key_->PushKey(KEY_INPUT_W);

	if (inputVec.length() >= 1.0f) dashVec_ = inputVec;
}

void Player::ChargeTrigger()
{
	// [SPACE]を押したら
	if (key_->TriggerKey(KEY_INPUT_SPACE)) {
		nowState_ = PlayerState::CHARGE;// -> チャージ状態に変更
		chargeSpeed_ = stdSpeed_;// -> チャージ速度に標準速度を代入
		chargeStartTime_ = GetNowCount();// -> チャージ開始時間を記録
	}
}