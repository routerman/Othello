#pragma once
#include "Disk.hpp"
#include "I2.hpp"

#define BLACK false
#define WHITE true

class Machine{
	bool active;
	bool color;
public:
	//‚»‚±‚ğ’u‚­‚Æ‘Šè‚ÉŠp‚ğ‚Æ‚ç‚ê‚é‚©’²‚×‚éŠÖ”
	bool corner_lose(bool color, int y,int x);
	void select(I2 *c,Disk s[][8]);
	Machine(){
		active=false;
	}
};

