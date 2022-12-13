#pragma once
#include "Vector2.h"

class Stage {
	// --メンバ変数-- //
public:

private:
	Vector2 pos_;// -> 座標
	float radius_;// -> 半径
	float maxRadius_;// -> 最高半径
	float minRadius_;// -> 最低半径
	float addRadius_;// -> 加算値

	bool isContr_;// 収縮しているかフラグ(している = true)
	float contrValue_;// -> 収縮値
	int contrStartTime_;// -> 収縮開始時間
	float contrTime_;// -> 収縮時間[s]
	float startContrRadius_;// -> 収縮開始時の半径

	// --メンバ関数-- //
public:
	// コンストラクタ
	Stage();

	// 初期化処理
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

	// 収縮開始
	void Contraction(float contrValue);

#pragma region ゲッター
	// 半径を取得
	float GetRadius() { return radius_; }
#pragma endregion

private:

};