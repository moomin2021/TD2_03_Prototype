#include "Player.h"
#include "DxLib.h"

Player::Player() :
	key_(nullptr),// -> �L�[�{�[�h����

	bullets_{},// -> �e

	// �v���C���[
	pos_{ 0.0f, 0.0f },// -> ���W
	radius_(0.0f),// ------> ���a
	speed_(0.0f),// -------> ���x

	// �{�X�̍��W
	bossPos_(nullptr)
{}

Player::~Player()
{

}

void Player::Initialize()
{
	// �L�[�{�[�h���̓N���X
	key_ = Key::GetInstance();

	// �v���C���[
	pos_ = { 700.0f, 500.0f };// -> ���W
	radius_ = 16.0f;// -----------> ���a
	speed_ = 2.0f;// -------------> ���x
}

void Player::Update()
{
	// �v���C���[��ԕʍX�V����
	(this->*actionTable[PlayerState::NORMAL])();

	// �e�̍X�V����
	for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
		it->Update();
	}
}

void Player::Draw()
{
	// �v���C���[�̕`��
	DrawCircleAA(pos_.x, pos_.y, radius_, 20, 0xFFFFFF, true);

	// �e�̕`�揈��
	for (auto it = bullets_.begin(); it != bullets_.end(); ++it) {
		it->Draw();
	}

	// �f�o�b�N�\��
	DrawFormatString(0, 20, 0xFFFFFF, "size = %d", bullets_.size());
}

void (Player::* Player::actionTable[]) () = {
	&Player::Normal,// -> �ʏ���
};

void Player::Normal()
{
	Move();// -> �ړ�����
	BulletShot();// -> �e�̔��ˏ���
	DeleteBullet();// -> �e�̍폜����
}

void Player::Move()
{
	pos_.x += (key_->PushKey(KEY_INPUT_D) - key_->PushKey(KEY_INPUT_A)) * speed_;
	pos_.y += (key_->PushKey(KEY_INPUT_S) - key_->PushKey(KEY_INPUT_W)) * speed_;
}

void Player::BulletShot()
{
	// �e���ˏ���
	if (key_->ReleaseKey(KEY_INPUT_SPACE)) {
		// �e�𐶐�
		Bullet* bullet = new Bullet();
		bullet->Initialize();// -> ����������
		bullet->SetPos(pos_);// -> ���W�ݒ�

		// �e�̈ړ�������ݒ�
		Vector2 p2bVec = *bossPos_ - pos_;// -> �v���C���[����{�X�܂ł̃x�N�g��
		p2bVec.normalize();// -> ���K��
		bullet->SetMoveVec(p2bVec);// -> �ړ�������ݒ�

		bullets_.push_back(*bullet);
	}
}

void Player::DeleteBullet()
{
	for (auto it = bullets_.begin();it != bullets_.end();) {
		// ��ʊO�ɍs������폜
		if (it->GetPos().x < -8.0f) it = bullets_.erase(it);
		else if (it->GetPos().x > 1008.0f) it = bullets_.erase(it);
		else if (it->GetPos().y < -8.0f) it = bullets_.erase(it);
		else if (it->GetPos().y > 1008.0f) it = bullets_.erase(it);
		else ++it;
	}
}
