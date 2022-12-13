#pragma once
#include "BaseScene.h"
#include "Key.h"
#include "Player.h"
#include "Boss.h"
#include "Stage.h"
#include "Enemy.h"
#include <vector>

class GameScene : public BaseScene {
	// --�����o�ϐ�-- //
public:

private:
	// �L�[�{�[�h����
	Key* key_;

	// �v���C���[
	Player* player_;

	// �{�X
	Boss* boss_;

	// �X�e�[�W
	Stage* stage_;

	// �G�l�~�[
	std::vector<Enemy*> enemys_;
	int maxEnemy_;

	// --�����o�֐�-- //
public:
	// �R���X�g���N�^
	GameScene();

	// �f�X�g���N�^
	~GameScene();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

private:
	void Collision();// -> �����蔻�菈��

};