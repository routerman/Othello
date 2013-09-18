#pragma once
#include "Disk.hpp"
class Machine{
	bool turn;
public:
	//‚»‚±‚ğ’u‚­‚Æ‘Šè‚ÉŠp‚ğ‚Æ‚ç‚ê‚é‚©’²‚×‚éŠÖ”
	bool corner_lose(bool color, int y,int x);
	void computer(bool color,int &m,int &n,Disk s[][8]);
};

