#pragma once
#include "Machine.hpp"

class Agent : public Machine{

public:
	void select(Disk disk[][8]);
};