#pragma once
#include "Stone.hpp"
class machine{
	bool turn;
public:
	//そこを置くと相手に角をとられるか調べる関数
	bool corner_lose(bool color, int y,int x);
	void computer(bool color,int &m,int &n,stone s[][8]);
};

