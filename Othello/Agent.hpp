#pragma once
#include "Machine.hpp"

class Agent : public Machine{
public:
	void select(I2 &cursor,Disk disk[][8]);
};