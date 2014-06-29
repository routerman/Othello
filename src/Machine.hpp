#pragma once

#include "Disk.hpp"
#include "I2.hpp"

/* �G�R���s���[�^�̑f�ƂȂ�N���X */
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