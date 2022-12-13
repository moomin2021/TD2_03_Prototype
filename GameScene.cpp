#include "GameScene.h"
#include "DxLib.h"
#include <random>

bool CircleCol(Vector2 pos1, float r1, Vector2 pos2, float r2) {
	float a = pos1.x - pos2.x;
	float b = pos1.y - pos2.y;
	float c = sqrtf(a * a + b * b);

	if (c <= r1 + r2) return true;
	return false;
}

int StageCircleCol(float stageR, Vector2 pos, float r1) {
	if (500.0f - stageR >= pos.x - r1) return 1;
	if (500.0f + stageR <= pos.x + r1) return 1;
	if (500.0f - stageR >= pos.y - r1) return 2;
	if (500.0f + stageR <= pos.y + r1) return 2;
	return 0;
}

GameScene::GameScene() :
	key_(nullptr),// -> �L�[�{�[�h����
	player_(nullptr),// -> �v���C���[
	boss_(nullptr),// -> �{�X
	stage_(nullptr),// -> �X�e�[�W
	maxEnemy_(0)// -> �ő�G�l�~�[��
{

}

GameScene::~GameScene()
{
	delete player_;
	delete boss_;
	delete stage_;
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

	// �X�e�[�W
	stage_ = new Stage();
	stage_->Initialize();

	// �v���C���[�ƃ{�X���݂��̍��W��ݒ肷��
	player_->SetBossPos(&boss_->GetPos());
	boss_->SetPlayerPos(&player_->GetPos());

	maxEnemy_ = 20;

	// �����_���ō��W������
	std::random_device device;
	std::mt19937 engine(device());
	std::uniform_real_distribution<float> rand(50.0f, 950.0f);

	for (size_t i = 0; i < maxEnemy_; i++) {
		Enemy* enemy = new Enemy();
		enemys_.emplace_back(enemy);
		enemys_[i]->Initialize();
		enemys_[i]->SetPos({ rand(engine), rand(engine) });
	}
}

void GameScene::Update()
{
	// �v���C���[
	player_->Update();

	// �{�X
	boss_->Update();

	// �X�e�[�W
	stage_->Update();

	for (size_t i = 0; i < maxEnemy_; i++) {
		enemys_[i]->Update();
	}

	// �����蔻�菈��
	Collision();
}

void GameScene::Draw()
{
	// �v���C���[
	player_->Draw();

	// �{�X
	boss_->Draw();

	// �X�e�[�W
	stage_->Draw();

	for (size_t i = 0; i < maxEnemy_; i++) {
		enemys_[i]->Draw();
	}

	DrawFormatString(0, 60, 0xFFFFFF, "stageRadius = %f", stage_->GetRadius());
}

void GameScene::Collision()
{
	// �v���C���[�ƃ{�X�̓����蔻��
	if (CircleCol(player_->GetPos(), player_->GetRadius(),
		boss_->GetPos(), boss_->GetRadius())) {
		// �{�X���m�[�}����Ԃ��v���C���[���_�b�V����ԂȂ�
		if (boss_->GetState() == Boss::BossState::NORMAL &&
			player_->GetState() == Player::PlayerState::DASH) {
			boss_->SetState(Boss::BossState::KNOCK);// -> �m�b�N�o�b�N��ԂɕύX
			
			// �v���C���[����{�X�ւ̃x�N�g�����m�b�N�o�b�N�x�N�g���Ƃ��Đݒ�
			Vector2 p2bVec = boss_->GetPos() - player_->GetPos();
			p2bVec.normalize();
			boss_->SetKnockVec(p2bVec);
			boss_->SetKnockSpeed(player_->GetSpeed());
			player_->GetDashVec() = -p2bVec;
		}
	}

	//// �v���C���[�ƃG�l�~�[�̓����蔻��
	//for (size_t i = 0; i < maxEnemy_; i++) {
	//	if (CircleCol(player_->GetPos(), player_->GetRadius(),
	//		enemys_[i]->GetPos(), enemys_[i]->GetRadius())) {

	//	}
	//}

	// �v���C���[�ƕǂ̓����蔻��
	int col = StageCircleCol(stage_->GetRadius(), player_->GetPos(), player_->GetRadius());
	if (col != 0 && player_->GetState() == Player::PlayerState::DASH) {
		if (col == 1) player_->GetDashVec().x = -player_->GetDashVec().x;
		if (col == 2) player_->GetDashVec().y = -player_->GetDashVec().y;
	}

	if (col != 0 && player_->GetState() == Player::PlayerState::NORMAL) {
		if (col == 1) {
			if (player_->GetPos().x >= 500.0f) {
				player_->GetPos().x = 500.0f + stage_->GetRadius();
			}
		}
	}

	col = StageCircleCol(stage_->GetRadius(), boss_->GetPos(), boss_->GetRadius());
	if (col != 0 && boss_->GetState() == Boss::BossState::KNOCK) {
		if (col == 1) boss_->GetKnockVec().x = -boss_->GetKnockVec().x;
		if (col == 2) boss_->GetKnockVec().y = -boss_->GetKnockVec().y;
		stage_->Contraction(10.0f);
	}
}
