#pragma once
#include "Stone.hpp"
class machine{
	bool turn;
public:
	//‚»‚±‚ğ’u‚­‚Æ‘Šè‚ÉŠp‚ğ‚Æ‚ç‚ê‚é‚©’²‚×‚éŠÖ”
	bool corner_lose(bool color, int y,int x);
	void computer(bool color,int &m,int &n,stone s[][8]);
};

