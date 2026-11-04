# include <Siv3D.hpp> // Siv3D v0.6.16

struct Cell{	// 各マスの状態を表す構造体
	bool visited = false;	// 迷路生成中に訪問したか
	bool topWall = true;	// 上側に壁がある
	bool rightWall = true;	// 右に壁がある
	bool bottomWall = true;	// 下に壁がある
	bool leftWall = true;	// 左に壁がある
};

void Main()
{
	constexpr int32 cellCount = 10;	// constexprは値がプログラム中に変わらないことを表す
	constexpr double cellSize = 50.0;
	const double gridSize = cellCount * cellSize;	// constは変数の値を一度決めた後変更できなくする
	const double left = (Scene::Width() - gridSize) / 2.0;
	const double top = (Scene::Height() - gridSize) / 2.0;
	
	const double padding = 3.0;	// スタート地点とゴール地点の塗りつぶしの範囲を少し小さくする

	while (System::Update())
	{
		Scene::SetBackground(Palette::White);	// 背景を白にする

		Cell cells[10][10];
		
		// 仮で左上のマスの右の壁を無くした
		cells[0][0].rightWall = false;
		cells[0][1].leftWall = false;
		
		for (int32 row = 0; row < cellCount; row++){
			for (int32 col = 0; col < cellCount; col++){
				const double x = left + col * cellSize;
				const double y = top + row * cellSize;
				
				// 壁の表示
				if (cells[row][col].topWall){
					Line{ x, y, x + cellSize, y }.draw(Palette::Black);
				}
				if (cells[row][col].rightWall){
					Line{ x + cellSize, y, x + cellSize, y + cellSize }.draw(Palette::Black);
				}
				if (cells[row][col].bottomWall){
					Line{ x, y + cellSize, x + cellSize, y + cellSize }.draw(Palette::Black);
				}
				if (cells[row][col].leftWall){
					Line{ x, y, x, y + cellSize }.draw(Palette::Black);
				}
				
				if (row == 0 && col == 0){	// スタート地点
					RectF{ x + padding, y + padding, cellSize - padding * 2, cellSize - padding * 2 }.draw(Palette::Blue);
				}
				else if (row == cellCount - 1 && col == cellCount -1){	// ゴール地点
					RectF{ x + padding, y + padding, cellSize - padding * 2, cellSize - padding * 2 }.draw(Palette::Red);
				}
			}
		}
		
	}
}
