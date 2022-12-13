#pragma once
#include "Vector2.h"

class Stage {
	// --�����o�ϐ�-- //
public:

private:
	Vector2 pos_;// -> ���W
	float radius_;// -> ���a
	float maxRadius_;// -> �ō����a
	float minRadius_;// -> �Œᔼ�a
	float addRadius_;// -> ���Z�l

	bool isContr_;// ���k���Ă��邩�t���O(���Ă��� = true)
	float contrValue_;// -> ���k�l
	int contrStartTime_;// -> ���k�J�n����
	float contrTime_;// -> ���k����[s]
	float startContrRadius_;// -> ���k�J�n���̔��a

	// --�����o�֐�-- //
public:
	// �R���X�g���N�^
	Stage();

	// ����������
	void Initialize();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	// ���k�J�n
	void Contraction(float contrValue);

#pragma region �Q�b�^�[
	// ���a���擾
	float GetRadius() { return radius_; }
#pragma endregion

private:

};