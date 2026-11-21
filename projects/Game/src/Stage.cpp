#include "Stage.hpp"	// Stage.hppを読み込み

Stage::Stage(){	// コンストラクタ
	mazeAutoGenerate();
}

// 迷路の自動生成
void Stage::mazeAutoGenerate(){
	Array<Point> stack;	// 行き止まりから戻るために前のマスを保存
	
	Point currentPos { 0, 0 };	// Point整数座標(xが列、yが行)
	cells[0][0].visited = true;	// スタートマスを訪問済みにする
	
	while (true){
		const int32 row = currentPos.y;	// 行
		const int32 col = currentPos.x;	// 列
		
		Array<int32> candidates;	// 候補
			
		// 候補を探す(0: 上、1: 右、2: 下、3: 左)
		if (row > 0 && !cells[row - 1][col].visited){
			candidates << 0; 	// 上
		}
		if (col + 1 < cellCount && !cells[row][col + 1].visited){
			candidates << 1;	// 右	<< Arrayに値を追加する書き方
		}
		if (row + 1 < cellCount && !cells[row + 1][col].visited){
			candidates << 2; 	// 下
		}
		if (col > 0 && !cells[row][col - 1].visited){
			candidates << 3; 	// 左
		}
			
		// 候補(0: 上、1: 右、2: 下、3: 左)があれば、候補からランダムに選び、壁を外す
		if (!candidates.isEmpty()){
			// 進む前のマスを保存
			stack << currentPos;
			
			// ランダムに候補を選ぶ
			const size_t index = Random<size_t>(0, candidates.size()-1);
			const int32 direction = candidates[index];
			
			Point nextPos = currentPos;
				
			// 選んだ候補の壁を外す
			if (direction == 0){	// 上
				cells[row][col].topWall = false;
				cells[row - 1][col].bottomWall = false;
				--nextPos.y;
			}
			else if (direction == 1){	// 右
				cells[row][col].rightWall = false;
				cells[row][col + 1].leftWall = false;
				++nextPos.x;
			}
			else if (direction == 2){	// 下
				cells[row][col].bottomWall = false;
				cells[row + 1][col].topWall = false;
				++nextPos.y;
			}
			else{	// 左
				cells[row][col].leftWall = false;
				cells[row][col - 1].rightWall = false;
				--nextPos.x;
			}
			
			currentPos = nextPos;
			cells[currentPos.y][currentPos.x].visited = true;
		}
		else if (!stack.isEmpty()){
			// 行き止まりなので、保存した前のマスへ戻る
			currentPos = stack.back();
			stack.pop_back();
		}
		else{
			// 戻る場所がなくなったら生成終了
			break;
		}
	}
}

// 迷路の描画
void Stage::draw() const{
	constexpr double cellSize = 50.0;
	const double gridSize = cellCount * cellSize;	// constは変数の値を一度決めた後変更できなくする
	const double left = (Scene::Width() - gridSize) / 2.0;
	const double top = (Scene::Height() - gridSize) / 2.0;
	const double padding = 3.0;	// スタート地点とゴール地点の塗りつぶしの範囲を少し小さくする
	
	for (int32 row = 0; row < cellCount; row++){
		for (int32 col = 0; col < cellCount; col++){
			const double x = left + col * cellSize;
			const double y = top + row * cellSize;
			
			// 先にスタートとゴールを塗る
			if (row == 0 && col == 0){	// スタート地点
				RectF{ x + padding, y + padding, cellSize - padding * 2, cellSize - padding * 2 }.draw(Palette::Blue);
			}
			else if (row == cellCount - 1 && col == cellCount -1){	// ゴール地点
				RectF{ x + padding, y + padding, cellSize - padding * 2, cellSize - padding * 2 }.draw(Palette::Red);
			}
			
			// 壁の表示
			if (cells[row][col].topWall){	// 上
				Line{ x, y, x + cellSize, y }.draw(Palette::Black);
			}
			if (cells[row][col].rightWall){	// 右
				Line{ x + cellSize, y, x + cellSize, y + cellSize }.draw(Palette::Black);
			}
			if (cells[row][col].bottomWall){	// 下
				Line{ x, y + cellSize, x + cellSize, y + cellSize }.draw(Palette::Black);
			}
			if (cells[row][col].leftWall){	// 左
				Line{ x, y, x, y + cellSize }.draw(Palette::Black);
			}
		}
	}
}

// fromのマスからtoのマスに進めるかどうかを返す
bool Stage::canMove(const Point& from, const Point& to) const{
	const int32 col = from.x;
	const int32 row = from.y;
	const int32 nextCol = to.x;
	const int32 nextRow = to.y;
	
	if (nextCol < 0 || nextCol >= cellCount
		|| nextRow < 0 || nextRow >= cellCount){	// 範囲外
		return false;
	}
	
	if (nextCol == col && nextRow == row - 1){	// 上
		return !cells[row][col].topWall;
	}
	if (nextCol == col + 1 && nextRow == row){	// 右
		return !cells[row][col].rightWall;
	}
	if (nextCol == col && nextRow == row + 1){	// 下
		return !cells[row][col].bottomWall;
	}
	if (nextCol == col - 1 && nextRow == row){	// 左
		return !cells[row][col].leftWall;
	}
	
	return false;
}

// マスの中心座標を返す
Vec2 Stage::cellCenter(const Point& cell) const{
	constexpr double cellSize = 50.0;
	constexpr double gridSize = cellCount * cellSize;
	const double left = (Scene::Width() - gridSize) / 2.0;
	const double top = (Scene::Height() - gridSize) / 2.0;
	
	return { left + (cell.x + 0.5) * cellSize,
		top + (cell.y + 0.5) * cellSize };
}

void Stage::mazeReset(){
	for (int32 row = 0; row < cellCount; ++row)
	{
		for (int32 col = 0; col < cellCount; ++col)
		{
			cells[row][col] = Cell{};
		}
	}
	
	mazeAutoGenerate();
}
