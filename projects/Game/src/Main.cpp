# include <Siv3D.hpp> // Siv3D v0.6.16
# include "Stage.hpp"
# include "Player.hpp"

void Main()
{
	Stage stage;
	Player player{ U"example/spritesheet/siv3d-kun-16.png" };	// siv3d-kunのキャラクターをインポート
	
	const Font clearFont{ 40 };		// クリア時に使うフォント
	const Font restartFont{ 30 };
	
	bool isCleared = false;
	
	while (System::Update())
	{
		Scene::SetBackground(Palette::White);	// 背景を白にする

		stage.draw();
		
		if (!isCleared){	// 迷路探索中
			player.update(stage);
		}
		else{	// ゴール後
			restartFont(U"スペースキーを押してリスタート").drawAt(Scene::Center().moveBy(0, 50), Palette::Black);
			if (KeySpace.down())
			{
				// 迷路ゲームをリスタートする
				stage.mazeReset();
				player.posReset();
				isCleared = false;
			}
		}

		if (player.cell() == stage.goalCenter()){
			isCleared = true;
			clearFont(U"クリア！").drawAt(Scene::Center(), Palette::Black);
		}
		
		player.draw(stage.cellCenter(player.cell()));
	}
}
