#pragma once
#include "machine.h"
#include "disk.h"
#include "i2.h"

#define BLACK false
#define WHITE true


/* Routermanの思考を埋め込んだコンピュータ(厨二www) */
class Routerman : public Machine{
	int weight[8][8];
public:
	//そこを置くと相手に角をとられるか調べる関数
	bool corner_lose(int x,int y,Disk s[][8]);
	void select();
	Routerman(bool color){
		this->color=color;
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
