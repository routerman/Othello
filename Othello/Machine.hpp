#pragma once

#include "Disk.hpp"
#include "I2.hpp"
class Machine{
protected:
	bool active;
	bool color;
public:
	void select(I2 &cursor,Disk disk[][8]);
};