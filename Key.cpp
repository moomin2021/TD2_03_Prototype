#include "Key.h"
#include "DxLib.h"

// インスタンス取得
Key* Key::GetInstance()
{
    // 関数内static変数として宣言
    static Key instance;
    return &instance;
}

// コンストラクタ
Key::Key() :
#pragma region 初期化リスト
    keys_{},// -> 現在の入力情報
    oldKeys_{}// -> 1フレーム前の入力情報
#pragma endregion
{}

// デストラクタ
Key::~Key() {}

// 更新処理
void Key::Update() {
    // 1フレーム前の情報を保存
    for (size_t i = 0; i < 256; i++) oldKeys_[i] = keys_[i];

    // 最新のキーボード情報を取得
    GetHitKeyStateAll(keys_);
}