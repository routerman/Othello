#pragma once

#include "Disk.hpp"
#include "I2.hpp"

/* �G�R���s���[�^�̑f�ƂȂ�N���X */
class Machine{
protected:
	bool active;
	bool color;
public:
	void setColor(bool color){this->color=color;}
	void select(I2 &cursor,Disk disk[][8]);
};