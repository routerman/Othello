#pragma once

#include "othello.h"
#include "i2.h"

/* 敵コンピュータの素となるクラス */
class Machine{
protected:
	bool color;
	I2 cursor;
	Othello othello_tmp;
public:
	void setColor(bool color){this->color=color;}
	void setOthello(Othello othello){
		this->othello_tmp = othello;
	}
	I2 getCursor(){return cursor;}
	virtual void select(){};
	//Machine(bool color){this->color=color;}
};
