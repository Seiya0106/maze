#include "Player.hpp"

Player::Player(const FilePath& imagePath)
	: m_texture(imagePath) {}

// プレイヤーの描画
void Player::draw(const Vec2& center) const{
	m_texture(0, 0, 20, 28)
		.resized(36, 50)
		.drawAt(center);
}
