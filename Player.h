#pragma once
#include "Key.h"
#include "Vector2.h"
#include "Bullet.h"
#include <vector>

class Player {
public:
	// ���
	enum PlayerState {
		NORMAL,// -> �m�[�}��
		CHARGE,// -> �`���[�W
		DASH// -> �_�b�V��
	};

	// --�����o�ϐ�-- //
public:

private:
	// �L�[�{�[�h���̓N���X
	Key* key_;

	// �v���C���[
	Vector2 pos_;// -> ���W
	float radius_;// -> ���a
	int nowState_;// -> ���݂̏��

	float stdSpeed_;// ----> �W�����x
	float nowSpeed_;// ----> ���݂̑��x
	float addSpeed_;// ----> ���x�̉��Z�l
	float subSpeed_;// ----> ���x�̌��Z�l
	float minSpeed_;// ----> ���x�̍ŏ��l
	float maxSpeed_;// ----> ���x�̍ō��l
	float chargeSpeed_;// -> �`���[�W�������x

	// �`���[�W
	float maxChargeTime_;// -> �ō��`���[�W����[s]
	int chargeStartTime_;// -> �`���[�W�J�n����

	Vector2 dashVec_;// -> �_�b�V������

	// �{�X�̍��W
	Vector2* bossPos_;

	// --�����o�֐�-- //
public:
	// �R���X�g���N�^
	Player();

	// �f�X�g���N�^
	~Player();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

#pragma region �Z�b�^�[
	// �{�X�̍��W��ݒ�
	void SetBossPos(Vector2* bossPos) { bossPos_ = bossPos; }
#pragma endregion

#pragma region �Q�b�^�[
	// ���W���擾����
	Vector2& GetPos() { return pos_; }

	// �_�b�V���x�N�g���擾
	Vector2& GetDashVec() { return dashVec_; }

	// ���a���擾
	float GetRadius() { return radius_; }

	// ��Ԃ��擾
	int GetState() { return nowState_; }

	// ���݂̑��x���擾
	float GetSpeed() { return nowSpeed_; }
#pragma endregion

private:
	// ��ԕʍX�V����
	static void (Player::* actionTable[]) ();

	// ��ԕʏ���
	void Normal();// -> �m�[�}����Ԏ�����
	void Charge();// -> �`���[�W��Ԏ�����
	void Dash();// ---> �_�b�V����Ԏ�����

	void Move();// -> �ړ�����
	void DashVec();// -> �_�b�V���x�N�g��
	void ChargeTrigger();// -> �`���[�W��Ԃւ̕ύX����
};