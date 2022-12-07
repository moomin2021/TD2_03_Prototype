#pragma once
#include "Key.h"
#include "Vector2.h"
#include "Bullet.h"
#include <vector>

class Player {
	// ���
	enum PlayerState {
		NORMAL// -> �ʏ�
	};

	// --�����o�ϐ�-- //
public:

private:
	// �L�[�{�[�h���̓N���X
	Key* key_;

	// �e
	std::vector<Bullet> bullets_;

	// �v���C���[
	Vector2 pos_;// -> ���W
	float radius_;// -> ���a
	float speed_;// -> ���x

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

	// �e���擾
	std::vector<Bullet> &GetBuulets() { return bullets_; }
#pragma endregion

private:
	// ��ԕʍX�V����
	static void (Player::* actionTable[]) ();

	// �ʏ���
	void Normal();

	void Move();// -> �ړ�����
	void BulletShot();// -> �e�̔��ˏ���
	void DeleteBullet();// -> �e�̍폜����
};