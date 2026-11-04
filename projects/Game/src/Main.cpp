# include <Siv3D.hpp> // Siv3D v0.6.16
# include "Stage.hpp"

void Main()
{
	Stage stage;
	while (System::Update())
	{
		Scene::SetBackground(Palette::White);	// 背景を白にする
		
		stage.draw();
	}
}
