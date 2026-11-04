#pragma once	// 「このヘッダーファイルを1つのコンパイル単位の中で1回だけインクルード（読み込み）する
#include <Siv3D.hpp>

class Stage;

class Player
{
public:
	Player(const FilePath& imagePath);	// コンストラクタ
	
	void update(const Stage& stage);
	Point cell() const { return m_cell; }
	
	void draw(const Vec2& center) const;
	
	void move() const;
private:
	Texture m_texture;	// キャラクターの表示
	Point m_cell{ 0, 0 };	// プレイヤーがどのマスにいるか
};
