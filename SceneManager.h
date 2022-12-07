#pragma once
#include "BaseScene.h"
#include "Key.h"

// シーン列挙型
enum SCENE {
	GAME
};

class SceneManager {
	// --禁止-- //
public:
	// コピーコンストラクタ
	SceneManager(const SceneManager& instance) = delete;

	// 代入演算子
	SceneManager& operator=(const SceneManager& instance) = delete;

	// --メンバ関数-- //
public:
	// インスタンス取得
	static SceneManager* GetInstance();

	// シーンを変更
	void ChangeScene(int sceneNo);

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

private:
	// コンストラクタ
	SceneManager();

	// デストラクタ
	~SceneManager();

	// --メンバ変数-- //
public:

private:
	// キーボード入力
	Key* key_;

	// 現在のシーン
	BaseScene* myScene_;

	// 現在のシーン番号
	int sceneNo_;
};