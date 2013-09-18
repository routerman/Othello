#pragma once
#include "Disk.hpp"
#include "I2.hpp"

#define BLACK false
#define WHITE true

class Machine{
	bool active;
	bool color;
public:
	//‚»‚±‚ð’u‚­‚Æ‘ŠŽè‚ÉŠp‚ð‚Æ‚ç‚ê‚é‚©’²‚×‚éŠÖ”
	bool corner_lose(bool color, int x,int y,Disk s[][8]);
	void select(I2 *c,Disk s[][8]);
	void setColor(bool color){this->color=color;}
	Machine(){
		active=false;
	}
};