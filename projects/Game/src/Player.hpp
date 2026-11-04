#pragma once	// 「このヘッダーファイルを1つのコンパイル単位の中で1回だけインクルード（読み込み）する
#include <Siv3D.hpp>

class Player
{
public:
	Player(const FilePath& imagePath);	// コンストラクタ
	
	void draw(const Vec2& center) const;
	
	void move() const;
private:
	Texture m_texture;	// キャラクターの表示
};
