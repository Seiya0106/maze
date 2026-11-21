# include <Siv3D.hpp> // Siv3D v0.6.16
# include "Stage.hpp"
# include "Player.hpp"

void Main()
{
	Stage stage;
	Player player{ U"example/spritesheet/siv3d-kun-16.png" };	// siv3d-kunのキャラクターをインポート
	
	const Font clearFont{ 40 };		// クリア時に使うフォント
	while (System::Update())
	{
		Scene::SetBackground(Palette::White);	// 背景を白にする

		stage.draw();
		
		player.update(stage);
		
		if (player.cell() == Point{9, 9}){
			clearFont(U"クリア！").drawAt(Scene::Center(), Palette::Black);
		}
		
		player.draw(stage.cellCenter(player.cell()));
	}
}
