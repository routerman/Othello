#pragma once
#include "Disk.hpp"
class Machine{
	bool turn;
public:
	//������u���Ƒ���Ɋp���Ƃ��邩���ׂ�֐�
	bool corner_lose(bool color, int y,int x);
	void computer(bool color,int &m,int &n,Disk s[][8]);
};

