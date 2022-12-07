#pragma once
#include "Vector2.h"

class Boss {
public:
	// ���
	enum BossState {
		NORMAL,// -> �ʏ���
		KNOCK,// --> �m�b�N�o�b�N���
	};

	// --�����o�ϐ�-- //
public:

private:
	// �{�X
	int state_;// ----> ���
	Vector2 pos_;// --> ���W
	float radius_;// -> ���a
	float speed_;// --> ���x

	// �m�b�N�o�b�N
	Vector2 knockVec_;// -> �m�b�N�o�b�N����
	float knockSpeed_;// -> �m�b�N�o�b�N���x

	// �v���C���[�̍��W
	Vector2* playerPos_;

	// --�����o�֐�-- //
public:
	// �R���X�g���N�^
	Boss();

	// �f�X�g���N�^
	~Boss();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

#pragma region �Z�b�^�[
	// �v���C���[�̍��W��ݒ�
	void SetPlayerPos(Vector2* playerPos) { playerPos_ = playerPos; }

	// ��Ԑݒ�
	void SetState(int state) { state_ = state; }

	// �m�b�N�o�b�N�����ݒ�
	void SetKnockVec(Vector2 knockVec) { knockVec_ = knockVec; }

	// �m�b�N�o�b�N���x�ݒ�
	void SetKnockSpeed(float knockSpeed) { knockSpeed_ = knockSpeed; }
#pragma endregion

#pragma region �Q�b�^�[
	// �{�X�̍��W���擾
	Vector2 &GetPos() { return pos_; }

	// ��Ԃ��擾
	int GetState() { return state_; }
#pragma endregion

private:
	// ��ԕʍX�V����
	static void (Boss::* actionTable[]) ();

	void Normal();// -> �ʏ���
	void Knock();// -> �m�b�N�o�b�N���

};