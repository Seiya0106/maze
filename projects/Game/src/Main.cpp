# include <Siv3D.hpp> // Siv3D v0.6.16

void Main()
{
	constexpr int32 cellCount = 10;	// constexprは値がプログラム中に変わらないことを表す
	constexpr double cellSize = 50.0;
	const double gridSize = cellCount * cellSize;	// constは変数の値を一度決めた後変更できなくする
	const double left = (Scene::Width() - gridSize) / 2.0;
	const double top = (Scene::Height() - gridSize) / 2.0;

	while (System::Update())
	{
		Scene::SetBackground(Palette::White);	// 背景を白にする

		// 縦線と横線をそれぞれ11本描いて、10×10のマス目にする
		for (int32 i = 0; i <= cellCount; ++i)
		{
			const double position = i * cellSize;
			Line{ left + position, top, left + position, top + gridSize }.draw(Palette::Black);
			Line{ left, top + position, left + gridSize, top + position }.draw(Palette::Black);
		}
	}
}
