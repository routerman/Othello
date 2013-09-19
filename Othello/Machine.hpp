#pragma once

#include "Disk.hpp"
#include "I2.hpp"

/* 敵コンピュータの素となるクラス */
class Machine{
protected:
	bool active;
	bool color;
public:
	void setColor(bool color){this->color=color;}
	void select(I2 &cursor,Disk disk[][8]);
};