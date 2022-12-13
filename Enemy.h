#pragma once
#include "Vector2.h"

class Enemy {
	// ���
	enum EnemyState {
		NORMAL,// -> �m�[�}�����
		KNOCK// -> �m�b�N�o�b�N���
	};

	// --�����o�ϐ�-- //
public:

private:
	Vector2 pos_;// -> ���W
	float radius_;// -> ���a
	int nowState_;// -> ���

	// --�����o�֐�-- //
public:
	// �R���X�g���N�^
	Enemy();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

#pragma region �Z�b�^�[
	// ���W��ݒ�
	void SetPos(Vector2 pos) { pos_ = pos; }
#pragma endregion

#pragma region �Q�b�^�[
	// ���W���擾
	Vector2 GetPos() { return pos_; }

	// ���a�̎擾
	float GetRadius() { return radius_; }
#pragma endregion

private:
	// ��ԕʍX�V����
	static void (Enemy::* actionTable[]) ();

	void Normal();// -> �ʏ���
	void Knock();// -> �m�b�N�o�b�N���
};