#pragma once
#include "Disk.hpp"
class Machine{
	bool turn;
public:
	//そこを置くと相手に角をとられるか調べる関数
	bool corner_lose(bool color, int y,int x);
	void computer(bool color,int &m,int &n,Disk s[][8]);
};

