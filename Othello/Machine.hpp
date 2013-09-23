#pragma once

#include "Disk.hpp"
#include "I2.hpp"

/* �G�R���s���[�^�̑f�ƂȂ�N���X */
class Machine{
protected:
	bool active;
	bool color;
	I2 cursor;
public:
	void setColor(bool color){this->color=color;}
	void select(Disk disk[][8]);
	I2 getCursor(){return cursor;}

};