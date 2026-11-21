#pragma once	// 「このヘッダーファイルを1つのコンパイル単位の中で1回だけインクルード（読み込み）する
#include <Siv3D.hpp>

class Stage;

class Player
{
public:
	Player(const FilePath& imagePath);	// コンストラクタ
	
	void update(const Stage& stage);
	void reset() { m_cell = Point{ 0, 0 }; }	// 移動　
	
	Point cell() const { return m_cell; }	// プレイヤーの現在位置を返す
	
	void draw(const Vec2& center) const;
	
	void posReset();	// プレイヤーの位置をスタート地点に戻す(オブジェクトの状態を変更するためconstはつけない)
	
private:
	Texture m_texture;	// キャラクターの表示
	Point m_cell{ 0, 0 };	// プレイヤーがどのマスにいるか
};
