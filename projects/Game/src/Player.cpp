#include "Player.hpp"
#include "Stage.hpp"

Player::Player(const FilePath& imagePath)
	: m_texture(imagePath) {}

void Player::update(const Stage& stage){
	Point next = m_cell;	// 次に進みたいマス
		
	// 移動キーの入力
	if (KeyUp.down()){
		--next.y;
	}
	else if (KeyRight.down()){
		++next.x;
	}
	else if (KeyDown.down()){
		++next.y;
	}
	else if (KeyLeft.down()){
		--next.x;
	}
	
	// 次のマスに移動可能であれば、移動を行う
	if (stage.canMove(m_cell, next)){
		m_cell = next;
	}
}

// プレイヤーの描画
void Player::draw(const Vec2& center) const{
	m_texture(0, 0, 20, 28)
		.resized(36, 50)
		.drawAt(center);	// 描画したいマスにプレイヤーを描く
}
