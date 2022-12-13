#include "Player.h"
#include "DxLib.h"
#include "Easing.h"

Player::Player() :
#pragma region ���������X�g
	key_(nullptr),// -> �L�[�{�[�h����

	// �v���C���[
	pos_{ 0.0f, 0.0f },// -> ���W
	radius_(0.0f),// ------> ���a
	nowState_(0),// -> ���݂̏��

	stdSpeed_(0.0f),// ----> �W�����x
	nowSpeed_(0.0f),// ----> ���݂̑��x
	addSpeed_(0.0f),// ----> ���x�̉��Z�l
	subSpeed_(0.0f),// ----> ���x�̌��Z�l
	minSpeed_(0.0f),// ----> ���x�̍ŏ��l
	maxSpeed_(0.0f),// ----> ���x�̍ō��l
	chargeSpeed_(0.0f),// -> �`���[�W�������x

	maxChargeTime_(0.0f),// -> �ō��`���[�W����
	chargeStartTime_(0),// -> �`���[�W�J�n����

	dashVec_{ 0.0f, 0.0f },// -> �_�b�V������

	// �{�X�̍��W
	bossPos_(nullptr)
#pragma endregion
{}

Player::~Player()
{

}

void Player::Initialize()
{
	// �L�[�{�[�h���̓N���X
	key_ = Key::GetInstance();

	// �v���C���[
	pos_ = { 700.0f, 500.0f };// -------> ���W
	radius_ = 16.0f;// -----------------> ���a
	nowState_ = PlayerState::NORMAL;// -> �m�[�}�����

	stdSpeed_ = 2.0f;// ---------> �W�����x
	nowSpeed_ = stdSpeed_;// ----> ���݂̑��x
	addSpeed_ = 0.1f;// --------> ���x�̉��Z�l
	subSpeed_ = 0.01f;// --------> ���x�̌��Z�l
	minSpeed_ = 0.1f;// ---------> ���x�̍ŏ��l
	maxSpeed_ = 10.0f;// --------> ���x�̍ō��l
	chargeSpeed_ = stdSpeed_;// -> �`���[�W�������x

	maxChargeTime_ = 3.0f;// -> �ō��`���[�W����[s]
	chargeStartTime_ = 0;// -> �`���[�W�J�n����

	dashVec_ = { -1.0f, 0.0f };// -> �������ɐݒ�
}

void Player::Update()
{
	// �v���C���[��ԕʍX�V����
	(this->*actionTable[nowState_])();
}

void Player::Draw()
{
	// �v���C���[�̕`��
	DrawCircleAA(pos_.x, pos_.y, radius_, 20, 0xFFFFFF, true);

	DrawFormatString(0, 20, 0xFFFFFF, "nowSpeed = %f", nowSpeed_);
	DrawFormatString(0, 40, 0xFFFFFF, "dashVec = { %f, %f }", dashVec_.x, dashVec_.y);
}

void (Player::* Player::actionTable[]) () = {
	&Player::Normal,// -> �m�[�}�����
	&Player::Charge,// -> �`���[�W���
	&Player::Dash,// ---> �_�b�V�����
};

void Player::Normal()
{
	Move();// -> �ړ�����
	ChargeTrigger();// -> �`���[�W��Ԃւ̕ύX����
	DashVec();
}

void Player::Charge()
{
	Move();// -> �ړ�����
	DashVec();

	// �`���[�W�J�n���Ԃ���̌o�ߎ���
	float nowTime = (GetNowCount() - chargeStartTime_) / 1000.0f;

	// �`���[�W��
	float chargeRate = nowTime / maxChargeTime_;
	if (chargeRate > 1.0f) chargeRate = 1.0f;// -> �`���[�W����1.0���傫��������1.0�ɌŒ�

	// �`���[�W���ő��x�ύX
	nowSpeed_ = Easing::Quint::easeOut(stdSpeed_, minSpeed_, chargeRate);

	// �`���[�W���Ń`���[�W���x��ύX
	chargeSpeed_ = Easing::Quint::easeOut(stdSpeed_ + 3.0f, maxSpeed_, chargeRate);

	// [SPACE]�𗣂�����
	if (key_->ReleaseKey(KEY_INPUT_SPACE)) {
		nowState_ = PlayerState::DASH;// -> �_�b�V����ԂɕύX
		nowSpeed_ = chargeSpeed_;// -> ���݂̑��x�Ƀ`���[�W���x����
	}
}

void Player::Dash()
{
	// ���x����
	nowSpeed_ -= 0.1f;

	// ���݂̑��x���W�����x�܂ŉ���������
	if (nowSpeed_ <= stdSpeed_) {
		nowSpeed_ = stdSpeed_;// -> �W�����x�ɐݒ�
		nowState_ = PlayerState::NORMAL;// -> �m�[�}����Ԃɐݒ�
	}

	// �_�b�V�������Ɉړ�
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
	// [SPACE]����������
	if (key_->TriggerKey(KEY_INPUT_SPACE)) {
		nowState_ = PlayerState::CHARGE;// -> �`���[�W��ԂɕύX
		chargeSpeed_ = stdSpeed_;// -> �`���[�W���x�ɕW�����x����
		chargeStartTime_ = GetNowCount();// -> �`���[�W�J�n���Ԃ��L�^
	}
}