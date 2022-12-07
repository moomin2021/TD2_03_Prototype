#pragma once
#include "Vector2.h"

class Bullet {
	// --�����o�ϐ�-- //
public:

private:
	Vector2 pos_;// -> ���W
	float radius_;// -> ���a
	float speed_;// -> ���x
	Vector2 moveVec_;// -> �ړ�����

	// --�����o�֐�-- //
public:
	// �R���X�g���N�^
	Bullet();

	// �f�X�g���N�^
	~Bullet();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

#pragma region �Z�b�^�[
	// ���W��ݒ�
	void SetPos(Vector2 pos) { pos_ = pos; }

	// �ړ�������ݒ�
	void SetMoveVec(Vector2 moveVec) { moveVec_ = moveVec; }
#pragma endregion

#pragma region �Q�b�^�[
	// ���W���擾
	Vector2 GetPos() { return pos_; }
#pragma endregion

private:

};