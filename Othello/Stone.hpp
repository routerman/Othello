#pragma once
class stone{
public:
	bool put;			//既に置いてあるかどうか
	bool color;			//色
	bool Canput_white;	//白が置けるか
	bool Canput_black;	//黒が置けるか
	//引数の示す場所と方向に裏返すことができる石が存在するかを返す関数
	//bool line(bool color,signed int y,signed int x,signed int dy,signed int dx);
	//石を裏返す関数
	//void reverse(bool color,signed int cy ,signed int cx);
	//盤全体を調べ、置ける場所が見つかればtrueを返す関数
	//bool CanPut(bool color);
};
