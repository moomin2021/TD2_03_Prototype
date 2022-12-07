#include "SceneManager.h"
#include "DxLib.h"
#include "GameScene.h"

// インスタンス取得
SceneManager* SceneManager::GetInstance() {
    // 関数内static変数として宣言
    static SceneManager instance;
    return &instance;
}

SceneManager::SceneManager() :
#pragma region 初期化リスト
    myScene_(nullptr),// -> 現在のシーン
    sceneNo_(0)// -> 現在のシーン番号
#pragma endregion
{
    // キーボード入力クラスのインスタンス取得
    key_ = Key::GetInstance();
}

// デストラクタ
SceneManager::~SceneManager() {
    // 現在のシーンが空ではなかったら
    if (myScene_ != nullptr) {
        // 現在のシーンをメモリ解放
        delete myScene_;
    }
}

// シーンを変更
void SceneManager::ChangeScene(int sceneNo) {
    // 現在のシーンが空ではなかったら
    if (myScene_ != nullptr) {
        // 現在のシーンをメモリ解放
        delete myScene_;
    }

    // 指定されたシーンのインスタンス生成と初期化
    switch (sceneNo)
    {
    case SCENE::GAME:
        myScene_ = new GameScene();// -> インスタンス生成
        myScene_->Initialize();// -> 現在のシーンの初期化処理
        sceneNo_ = SCENE::GAME;// -> 現在のシーン番号を変更
        break;
    }
}

// 更新処理
void SceneManager::Update() {
    //// [SPACE]キーでシーンを変更
    //if (key_->TriggerKey(KEY_INPUT_SPACE)) {
    //    // 現在のシーン番号を進める
    //    sceneNo_++;

    //    // 現在のシーン番号が最大値以上なら
    //    if (sceneNo_ > SCENE::GAME) {
    //        // 現在のシーン番号を0にする
    //        sceneNo_ = 0;
    //    }

    //    // シーンを変更する
    //    ChangeScene(sceneNo_);
    //}

    // 現在のシーンの更新処理
    myScene_->Update();
}

// 描画処理
void SceneManager::Draw() {
    // 現在のシーンの描画処理
    myScene_->Draw();
}