#pragma once

class Key {
	// --禁止-- //
public:
	// コピーコンストラクタ
	Key(const Key& instance) = delete;

	// 代入演算子
	Key& operator=(const Key& instance) = delete;

	// --メンバ関数-- //
public:
	// インスタンス取得
	static Key* GetInstance();

	// 更新処理
	void Update();

	/// <summary>
	/// キーが押されているか
	/// </summary>
	/// <param name="key"> キー指定 </param>
	bool PushKey(int key) { return keys_[key]; }

	/// <summary>
	/// キーが押された瞬間か
	/// </summary>
	/// <param name="key"> キー指定 </param>
	/// <returns></returns>
	bool TriggerKey(int key) { return (keys_[key] && !oldKeys_[key]); }

	/// <summary>
	/// キーが離された瞬間か
	/// </summary>
	/// <param name="key"> キー指定 </param>
	/// <returns></returns>
	bool ReleaseKey(int key) { return (!keys_[key] && oldKeys_[key]); }

private:
	// コンストラクタ
	Key();

	// デストラクタ
	~Key();

	// --メンバ変数-- //
public:

private:
	// 現在の入力情報
	char keys_[256];

	// 1フレーム前の入力情報
	char oldKeys_[256];

};