#pragma once
#include "Machine.hpp"

class Agent : public Machine{

public:
	void select();
	Agent(bool color){this->color=color;}
};