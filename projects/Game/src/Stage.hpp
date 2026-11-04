#pragma once	// 「このヘッダーファイルを1つのコンパイル単位の中で1回だけインクルード（読み込み）する
#include <Siv3D.hpp>

class Stage
{
public:
	Stage();
		
	// 迷路の描画処理
	void draw() const;
	
	Vec2 startCenter() const;	// スタート地点の取得

private:
	struct Cell{	// 各マスの状態を表す構造体
		bool visited = false;	// 迷路生成中に訪問したか
		bool topWall = true;	// 上側に壁がある
		bool rightWall = true;	// 右に壁がある
		bool bottomWall = true;	// 下に壁がある
		bool leftWall = true;	// 左に壁がある
	};
	
	static constexpr int32 cellCount = 10;	// constexprは値がプログラム中に変わらないことを表す、staticはオブジェクトではなくクラス全体で共有する値である
	Cell cells[cellCount][cellCount];	// マスの2次元配列
	
	void mazeAutoGenerate();	// 迷路の自動生成する関数
};
