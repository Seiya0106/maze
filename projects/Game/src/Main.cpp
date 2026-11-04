# include <Siv3D.hpp> // Siv3D v0.6.16
# include "Stage.hpp"
# include "Player.hpp"

void Main()
{
	Stage stage;
	Player player{ U"example/spritesheet/siv3d-kun-16.png" };	// siv3d-kunのキャラクターをインポート
	while (System::Update())
	{
		Scene::SetBackground(Palette::White);	// 背景を白にする
		
		// 描画
		stage.draw();
		player.draw(stage.startCenter());
	}
}
