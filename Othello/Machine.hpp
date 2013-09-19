#pragma once
#include "Disk.hpp"
#include "I2.hpp"

#define BLACK false
#define WHITE true

class Machine{
	bool active;
	bool color;
	int weight[8][8];
public:
	//‚»‚±‚ð’u‚­‚Æ‘ŠŽè‚ÉŠp‚ð‚Æ‚ç‚ê‚é‚©’²‚×‚éŠÖ”
	bool corner_lose(int x,int y,Disk s[][8]);
	void select(I2 &c,Disk s[][8]);
	void setColor(bool color){this->color=color;}
	Machine(){
		active=false;
		int init[8][8]={
			{9,2,8,5,5,8,2,9},
			{2,1,4,7,7,4,1,2},
			{8,4,6,5,5,6,4,8},
			{5,7,5,0,0,5,7,5},
			{5,7,5,0,0,5,7,5},
			{8,4,6,5,5,6,4,8},
			{2,1,4,7,7,4,1,2},
			{9,2,8,5,5,8,2,9}
		};
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				weight[i][j]=init[i][j];
			}
		}
	}
};