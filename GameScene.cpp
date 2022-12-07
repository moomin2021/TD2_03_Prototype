#include "GameScene.h"

bool CircleCol(Vector2 pos1, float r1, Vector2 pos2, float r2) {
	float a = pos1.x - pos2.x;
	float b = pos1.y - pos2.y;
	float c = sqrtf(a * a + b * b);

	if (c <= r1 + r2) return true;
	return false;
}

GameScene::GameScene() :
	key_(nullptr),// -> �L�[�{�[�h����
	player_(nullptr),// -> �v���C���[
	boss_(nullptr)// -> �{�X
{

}

GameScene::~GameScene()
{
	delete player_;
	delete boss_;
}

void GameScene::Initialize()
{
	// �L�[�{�[�h����
	key_ = Key::GetInstance();

	// �v���C���[
	player_ = new Player();
	player_->Initialize();

	// �{�X
	boss_ = new Boss();
	boss_->Initialize();

	// �v���C���[�ƃ{�X���݂��̍��W��ݒ肷��
	player_->SetBossPos(&boss_->GetPos());
	boss_->SetPlayerPos(&player_->GetPos());
}

void GameScene::Update()
{
	// �v���C���[
	player_->Update();

	// �{�X
	boss_->Update();

	// �����蔻�菈��
	Collision();
}

void GameScene::Draw()
{
	// �v���C���[
	player_->Draw();

	// �{�X
	boss_->Draw();
}

void GameScene::Collision()
{
	for (auto it = player_->GetBuulets().begin(); it != player_->GetBuulets().end();) {
		// �{�X�ɓ���������e���폜
		if (CircleCol(it->GetPos(), 8.0f, boss_->GetPos(), 64.0f)) {
			// �{�X�̏�Ԃ��ʏ��ԂȂ�
			if (boss_->GetState() == Boss::BossState::NORMAL) {
				boss_->SetState(Boss::BossState::KNOCK);// -> �m�b�N��ԂɕύX
				boss_->SetKnockSpeed(2.0f);// -> �m�b�N�o�b�N�̑��x��ݒ�

				// �e����{�X�܂ł̃x�N�g�����v�Z
				Vector2 b2bVec = boss_->GetPos() - it->GetPos();
				b2bVec.normalize();// -> ���K��
				boss_->SetKnockVec(b2bVec);// -> �m�b�N�o�b�N�̕�����ݒ�
			}

			// ���������e���폜
			it = player_->GetBuulets().erase(it);
		}
		else ++it;
	}
}
