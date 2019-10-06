#include <iostream>
#include "Transition.h"

Transition::Transition(string _name)
{
	this->name = _name;
}

string Transition::getName()
{
	return name;
}

string Transition::getType()
{
	return "Transition";
}


