#pragma once

#include "disk.h"
#include "i2.h"

/* 敵コンピュータの素となるクラス */
class Machine{
protected:
	bool color;
	I2 cursor;
	Disk disk[8][8];
public:
	void setColor(bool color){this->color=color;}
	virtual void select(){};
	void setDisk(Disk disk[][8]){
		for(int x=0;x<8;x++){
			for(int y=0;y<8;y++){
				this->disk[x][y]=disk[x][y];
			}
		}
	}
	I2 getCursor(){return cursor;}
	//Machine(bool color){this->color=color;}
};
